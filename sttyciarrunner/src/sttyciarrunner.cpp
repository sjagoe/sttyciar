#include <iostream>

#include <QFile>
#include <QMessageBox>

#include "abstractionlayer.hh"
#include "statisticslayer.hh"
#include "packetdumper.hh"
#include "alnetworklistener.hh"
#include "networklogiclayer.hh"

#include "sttyciarrunner.hh"
#include "sttyciarui_gui.hh"
#include "nllhub.hh"
#include "nllswitch.hh"

const int SttyciarRunner::NLL_UPDATE_TIMEOUT_MSEC;
const int SttyciarRunner::STAT_UPDATE_TIMEOUT_MSEC;

const short SttyciarRunner::HUB_TYPE;
const short SttyciarRunner::SWITCH_TYPE;

const int SttyciarRunner::PDUMP_LINKTYPE;

const int SttyciarRunner::PACKET_CAPTURE_SIZE;
const int SttyciarRunner::PCAP_READ_TIMEOUT;

SttyciarRunner::SttyciarRunner()
{
    this->_sttyciarRunning = false;
    // create the timer that will signal the NLL to update
    this->_nllUpdateTimer.reset( new QTimer );
    this->_nllUpdateTimer->setInterval( NLL_UPDATE_TIMEOUT_MSEC );

    connect( this->_nllUpdateTimer.get(), SIGNAL( timeout() ),
        this, SLOT( nllUpdateTimeout() ) );

    // create the timer that will tell the statistics layer to update
    this->_statisticsUpdateTimer.reset( new QTimer );
    this->_statisticsUpdateTimer->setInterval( STAT_UPDATE_TIMEOUT_MSEC );

    connect( this->_statisticsUpdateTimer.get(), SIGNAL( timeout() ),
        this, SLOT( statisticsUpdateTimeout() ) );

    // set up the list of available devices (i.e. hub, switch, etc)
    this->_availableDevices.insert( SttyciarRunner::HUB_TYPE,
        QString("Ethernet Hub") );
    this->_availableDevices.insert( SttyciarRunner::SWITCH_TYPE,
        QString("Ethernet Switch") );

    // create the abstraction layer
    this->_abstractionLayer.reset( new AbstractionLayer );

    // create the Statistics Layer
    //this->_statisticsLayer.reset( new StatisticsLayer );

//    shared_ptr<ALStatisticsListener> sl = this->_statisticsLayer;
//
//    // Register the SL with the AL
//    this->_abstractionLayer->registerSL( sl );

    // create the user interface with the list of available devices
    // (hub, switch)
    this->_ui.reset( new SttyciarGUI( this->_availableDevices ) );

    // connect the signals from the UI
    connect( this->_ui.get(), SIGNAL(exitSttyciar()),
        this, SLOT(exitSttyciar()));
    connect( this->_ui.get(),
        SIGNAL( startSttyciar(QString, shared_ptr<QStringList>, QString) ),
        this, SLOT( startSttyciar(QString, shared_ptr<QStringList>, QString) ) );
    connect( this->_ui.get(), SIGNAL( stopSttyciar() ),
        this, SLOT( stopSttyciar() ) );
    connect( this->_ui.get(), SIGNAL( restartSttyciar( const QString&,
                                                const shared_ptr<QStringList>&,
                                                const QString& ) ),
        this, SLOT( restartSttyciar( const QString&,
                                    const shared_ptr<QStringList>&,
                                    const QString& ) ) );

    // tell the UI about the available network interfaces
    this->_ui->receiveDevices( this->_abstractionLayer->getDevices() );
}

void SttyciarRunner::startSttyciar(QString deviceType,
    shared_ptr<QStringList> devices, QString dumpFile)
{
    // check if dumping is enabled, and prepare (delete existing) the dumpfile
    bool dumpEnabled = true;
    if (dumpFile == QString())
    {
        dumpEnabled = false;
    }

    bool startRunning = false;
    if (!dumpEnabled)
        startRunning = true;
    else
    {
        QFile file(dumpFile);
        if (file.exists())
        {
            startRunning = QMessageBox::warning( 0,
                tr("Overwrite Dump File"),
                tr( "The dump file will be overwritten. Continue?" ),
                QMessageBox::Yes | QMessageBox::No, QMessageBox::No );
            if (startRunning)
            {
                file.remove();
            }
        }
        else
        {
            startRunning = true;
        }
    }

    if ( startRunning )
    {
//<<<<<<< TREE
        try // try to start the system. Catch the exception thown by AbstractionLayer::
        {
            // activate the selected devices in the abstraction layer
            this->_abstractionLayer->activateDevices( devices );

            int type = this->_availableDevices.key( deviceType );
            switch ( type )
            {
                case SttyciarRunner::HUB_TYPE:
                {
                    // create the NLL
                    this->_networkLogicLayer.reset( new NLLHub );

                    break;
                }
                case SttyciarRunner::SWITCH_TYPE:
                {
                    // create the NLL
                    this->_networkLogicLayer.reset( new NLLSwitch );

                    break;
                }
            }
            if (this->_networkLogicLayer.get() != 0)
            {
                // connect the signal to update the NLL
                connect( this, SIGNAL( updateNLL(int) ), this->_networkLogicLayer.get(),
                    SLOT( update(int) ) );

                // tell the AL and NLL about each other
                weak_ptr<ALNetworkListener> weakNLL(this->_networkLogicLayer);
                this->_abstractionLayer->registerNLL(weakNLL);
                weak_ptr<AbstractionLayer> weakAL(this->_abstractionLayer);
                this->_networkLogicLayer->registerAbstractionLayer(weakAL);

                // create the packet dumper
                this->_packetDumper.reset( new PacketDumper( PDUMP_LINKTYPE,
                    PACKET_CAPTURE_SIZE, dumpFile, dumpEnabled ) );

                weak_ptr<PacketDumper> dumper( this->_packetDumper );

                this->_abstractionLayer->openActivatedDevices(PACKET_CAPTURE_SIZE,
                                      PCAP_READ_TIMEOUT);
                // get the activated device list
                QList<shared_ptr<Device> > activatedDevices =
                    this->_abstractionLayer->getActivatedDevices();
                // send the activated devices to the UI
                this->_ui->receiveActivatedDevices( activatedDevices );

                // create the statistics layer and initialize the map of devices using
                // the currently activated devices
                this->_statisticsLayer.reset(new StatisticsLayer(activatedDevices, dumper));
                shared_ptr<ALStatisticsListener> sl = this->_statisticsLayer;
                // Register the SL with the AL
                this->_abstractionLayer->registerSL( sl );

                this->_statisticsLayer->reset();

                // connect the Statistics Layer
                connect( this, SIGNAL(updateStatistics(int)),
                    this->_statisticsLayer.get(), SLOT( calculate(int) ) );
                connect( this->_statisticsLayer.get(),
                    SIGNAL( sendStats(shared_ptr<Statistics>&) ),
                    this->_ui.get(), SLOT( updateStatistics( shared_ptr<Statistics>& ) ) );

    //            this->_abstractionLayer->setFilterEnabled(true);

                // store that we are now running
                this->_sttyciarRunning = true;

                // start the system
                this->_networkLogicLayer->start();
                this->_packetDumper->start();
                this->_statisticsLayer->start();
                this->_abstractionLayer->startListening();

                this->_nllUpdateTimer->start();
                this->_statisticsUpdateTimer->start();
                this->_ui->sttyciarRunning();
            }
        }
        catch (CannotStartListeningException e) // If this exception is thrown, the system could not be started. clean up!
        {
            if (this->_networkLogicLayer.get() != 0)
            {
                // make sure the timers are stopped
                this->_nllUpdateTimer->stop();
                this->_statisticsUpdateTimer->stop();

                // make sure the UI is in the correct state
                this->_sttyciarRunning = false;
                this->_ui->sttyciarStopped();

                // close and deactivate the previously activated devices
                this->_abstractionLayer->clearActivatedDevices();

                // disconnect the Statistics Layer
                disconnect( this, SIGNAL(updateStatistics(int)),
                    this->_statisticsLayer.get(), SLOT( calculate(int) ) );
                disconnect( this->_statisticsLayer.get(),
                    SIGNAL( sendStats(shared_ptr<Statistics>&) ),
                    this->_ui.get(), SLOT( updateStatistics( shared_ptr<Statistics>& ) ) );

                // destroy the statistics layer
                this->_abstractionLayer->restoreDefaultStatisticsLayer();
                this->_statisticsLayer.reset();
                // destroy the dumper
                this->_packetDumper.reset();

                disconnect( this, SIGNAL( updateNLL(int) ), this->_networkLogicLayer.get(),
                    SLOT( update(int) ) );

                this->_networkLogicLayer.reset();
            }
//=======
//        // activate the selected devices in the abstraction layer
//        this->_abstractionLayer->activateDevices( devices );
//        // get the activated device list
//        QList<shared_ptr<Device> > activatedDevices =
//            this->_abstractionLayer->getActivatedDevices();
//        // send the activated devices to the UI
//        this->_ui->receiveActivatedDevices( activatedDevices );
//
//        int type = this->_availableDevices.key( deviceType );
//        switch ( type )
//        {
//            case SttyciarRunner::HUB_TYPE:
//            {
//                // create the NLL
//                this->_networkLogicLayer.reset( new NLLHub );
//
//                break;
//            }
//            case SttyciarRunner::SWITCH_TYPE:
//            {
//                // create the NLL
//                this->_networkLogicLayer.reset( new NLLSwitch );
//
//                break;
//            }
//        }
//
//        if (this->_networkLogicLayer.get() != 0)
//        {
//            // connect the signal to update the NLL
//            connect( this, SIGNAL( updateNLL(int) ), this->_networkLogicLayer.get(),
//                SLOT( update(int) ) );
//
//            // tell the AL and NLL about each other
//            weak_ptr<ALNetworkListener> weakNLL(this->_networkLogicLayer);
//            this->_abstractionLayer->registerNLL(weakNLL);
//            weak_ptr<AbstractionLayer> weakAL(this->_abstractionLayer);
//            this->_networkLogicLayer->registerAbstractionLayer(weakAL);
//
//            // create the packet dumper
//            this->_packetDumper.reset( new PacketDumper( PDUMP_LINKTYPE,
//                PACKET_CAPTURE_SIZE, dumpFile, dumpEnabled ) );
//
//            weak_ptr<PacketDumper> dumper( this->_packetDumper );
//
//            // create the statistics layer and initialize the map of devices using
//            // the currently activated devices
//            this->_statisticsLayer.reset(new StatisticsLayer(activatedDevices, dumper));
//            shared_ptr<ALStatisticsListener> sl = this->_statisticsLayer;
//            // Register the SL with the AL
//            this->_abstractionLayer->registerSL( sl );
//
//            this->_statisticsLayer->reset();
//
//            // connect the Statistics Layer
//            connect( this, SIGNAL(updateStatistics(int)),
//                this->_statisticsLayer.get(), SLOT( calculate(int) ) );
//            connect( this->_statisticsLayer.get(),
//                SIGNAL( sendStats(shared_ptr<Statistics>&) ),
//                this->_ui.get(), SLOT( updateStatistics( shared_ptr<Statistics>& ) ) );
//
//            // store that we are now running
//            this->_sttyciarRunning = true;
//
//            // start the system
//            this->_networkLogicLayer->start();
//            this->_packetDumper->start();
//            this->_statisticsLayer->start();
////            this->_abstractionLayer->setFilterEnabled(true);
//            this->_abstractionLayer->startListening();
//
//            this->_ui->sttyciarRunning();
//
//            this->_nllUpdateTimer->start();
//            this->_statisticsUpdateTimer->start();
//            this->_ui->sttyciarRunning();
//>>>>>>> MERGE-SOURCE
        }
    }
}

void SttyciarRunner::stopSttyciar()
{
    std::cout << "SttyciarRunner::stopSttyciar()" << std::endl;
    // make sure the timers are stopped
    this->_nllUpdateTimer->stop();
    this->_statisticsUpdateTimer->stop();

    this->_sttyciarRunning = false;
    std::cout << "1" << std::endl;
    // stop the statisticslayer
    if (this->_statisticsLayer.get() != 0)
    {
        std::cout << "if (this->_statisticsLayer.get() != 0)" << std::endl;
        // disconnect the Statistics Layer
        disconnect( this, SIGNAL(updateStatistics(int)),
            this->_statisticsLayer.get(), SLOT( calculate(int) ) );
        disconnect( this->_statisticsLayer.get(),
            SIGNAL( sendStats(shared_ptr<Statistics>&) ),
            this->_ui.get(), SLOT( updateStatistics( shared_ptr<Statistics>& ) ) );

        this->_statisticsLayer->stopRunning();
    }
    std::cout << "2" << std::endl;
    // stop the abstractionlayer from listeneing for packets
    if (this->_abstractionLayer.get() != 0)
    {
        std::cout << "if (this->_abstractionLayer.get() != 0)" << std::endl;
        this->_abstractionLayer->stopListening();
        std::cout << "2a" << std::endl;
        // destroy the statistics layer
        this->_statisticsLayer.reset();
        std::cout << "2b" << std::endl;
    }
    std::cout << "3" << std::endl;
    // stop the NLL from processing packets
    if (this->_networkLogicLayer.get() != 0)
    {
        std::cout << "if (this->_networkLogicLayer.get() != 0)" << std::endl;
        disconnect( this, SIGNAL( updateNLL(int) ), this->_networkLogicLayer.get(),
            SLOT( update(int) ) );
        this->_networkLogicLayer->exitNow();
    }
    std::cout << "4" << std::endl;
    if (this->_packetDumper.get() != 0)
        this->_packetDumper->stop();
    std::cout << "5" << std::endl;
    // destroy the AL and NLL objects
    this->_networkLogicLayer.reset();
    // notify the UI
    this->_ui->sttyciarStopped();
    std::cout << "6" << std::endl;
}

void SttyciarRunner::exitSttyciar()
{
    if (this->_sttyciarRunning)
    {
        stopSttyciar();
    }
    emit exit();
//    _abstractionLayer.reset();
//    _ui.reset();
}

void SttyciarRunner::nllUpdateTimeout()
{
    emit updateNLL( this->_nllUpdateTimer->interval() );
}

void SttyciarRunner::statisticsUpdateTimeout()
{
    emit updateStatistics( this->_statisticsUpdateTimer->interval() );
}

void SttyciarRunner::restartSttyciar( const QString& deviceType,
    const shared_ptr<QStringList>& devices, const QString& dumpFile )
{
    stopSttyciar();
    startSttyciar( deviceType, devices, dumpFile );
}
