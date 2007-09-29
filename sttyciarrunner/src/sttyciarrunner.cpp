//#include <iostream>

#include "abstractionlayer.hh"
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

const int SttyciarRunner::PACKET_CAPTURE_SIZE;
const int SttyciarRunner::PCAP_READ_TIMEOUT;

SttyciarRunner::SttyciarRunner()
{
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

    // create the user interface with the list of available devices
    // (hub, switch)
    this->_ui.reset( new SttyciarGUI( this->_availableDevices ) );

    // connect the signals from the UI
    connect( this->_ui.get(), SIGNAL(exitSttyciar()),
        this, SLOT(exitSttyciar()));
    connect( this->_ui.get(),
        SIGNAL( startSttyciar(QString, shared_ptr<QStringList>) ),
        this, SLOT( startSttyciar(QString, shared_ptr<QStringList>) ) );
    connect( this->_ui.get(), SIGNAL( stopSttyciar() ),
        this, SLOT( stopSttyciar() ) );

    // tell the UI about the available network interfaces
    this->_ui->receiveDevices( this->_abstractionLayer->getDevices() );
}

void SttyciarRunner::startSttyciar(QString deviceType,
    shared_ptr<QStringList> devices)
{
    int type = this->_availableDevices.key( deviceType );
    switch ( type )
    {
        case SttyciarRunner::HUB_TYPE:
        {
            // activate the selected devices in the abstraction layer
            this->_abstractionLayer->activateDevices( devices );
            // get the activated device list
            QList<shared_ptr<Device> > activatedDevices =
                this->_abstractionLayer->getActivateDevices();
            // send the activated devices to the UI
            this->_ui->receiveActivatedDevices( activatedDevices );

            // create the NLL
            this->_networkLogicLayer.reset( new NLLHub );

            break;
        }
        case SttyciarRunner::SWITCH_TYPE:
        {
            // activate the selected devices in the abstraction layer
            this->_abstractionLayer->activateDevices( devices );
            // get the activated device list
            QList<shared_ptr<Device> > activatedDevices =
                this->_abstractionLayer->getActivateDevices();
            // send the activated devices to the UI
            this->_ui->receiveActivatedDevices( activatedDevices );

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

        // start the system
        this->_networkLogicLayer->start();
        this->_abstractionLayer->startListening(PACKET_CAPTURE_SIZE,
                                          PCAP_READ_TIMEOUT);
        this->_ui->sttyciarRunning();
    }
}

void SttyciarRunner::stopSttyciar()
{
    // stop the abstractionlayer from listeneing for packets
    if (this->_abstractionLayer.get() != 0)
        this->_abstractionLayer->stopListening();
    // stop the NLL from processing packets
    if (this->_networkLogicLayer.get() != 0)
    {
        this->_networkLogicLayer->exitNow();
        this->_networkLogicLayer->wait();
    }
    // destroy the AL and NLL objects
    this->_networkLogicLayer.reset();
    // notify the UI
    this->_ui->sttyciarStopped();
}

void SttyciarRunner::exitSttyciar()
{
    stopSttyciar();
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
