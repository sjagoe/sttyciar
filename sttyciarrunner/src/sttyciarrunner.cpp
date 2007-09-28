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
    this->_nllUpdateTimer.reset( new QTimer );
    this->_nllUpdateTimer->setInterval( NLL_UPDATE_TIMEOUT_MSEC );

    connect( this->_nllUpdateTimer.get(), SIGNAL( timeout() ), this, SLOT( nllUpdateTimeout() ) );

    this->_statisticsUpdateTimer.reset( new QTimer );
    this->_statisticsUpdateTimer->setInterval( STAT_UPDATE_TIMEOUT_MSEC );

    this->_availableDevices.insert( SttyciarRunner::HUB_TYPE, QString("Ethernet Hub") );
    this->_availableDevices.insert( SttyciarRunner::SWITCH_TYPE, QString("Ethernet Switch") );

    this->_abstractionLayer.reset( new AbstractionLayer );

    this->_ui.reset( new SttyciarGUI( this->_availableDevices ) );

    connect( this->_ui.get(), SIGNAL(exitSttyciar()), this, SLOT(exitSttyciar()));

    connect( this->_ui.get(),
        SIGNAL( startSttyciar(QString, shared_ptr<QStringList>) ),
        this, SLOT( startSttyciar(QString, shared_ptr<QStringList>) ) );

    connect( this->_ui.get(), SIGNAL( stopSttyciar() ), this, SLOT( stopSttyciar() ) );

    this->_ui->receiveDevices( this->_abstractionLayer->getDevices() );
}

void SttyciarRunner::startSttyciar(QString deviceType,
    shared_ptr<QStringList> devices)
{
    //std::cout << deviceType.toStdString() << std::endl;
    int type = this->_availableDevices.key( deviceType );
    switch ( type )
    {
        case SttyciarRunner::HUB_TYPE:
        {
            // activate the selected devices in the abstraction layer
            this->_abstractionLayer->activateDevices( devices );
            // get the activated device list
            QList<shared_ptr<Device> > activatedDevices = this->_abstractionLayer->getActivateDevices();
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
            QList<shared_ptr<Device> > activatedDevices = this->_abstractionLayer->getActivateDevices();
            // send the activated devices to the UI
            this->_ui->receiveActivatedDevices( activatedDevices );

            // create the NLL
            this->_networkLogicLayer.reset( new NLLSwitch );

            break;
        }
    }

    if (this->_networkLogicLayer.get() != 0)
    {
        connect( this, SIGNAL( updateNLL(int) ), this->_networkLogicLayer.get(), SLOT( update(int) ) );

        weak_ptr<ALNetworkListener> weakNLL(this->_networkLogicLayer);
        this->_abstractionLayer->registerNLL(weakNLL);
        weak_ptr<AbstractionLayer> weakAL(this->_abstractionLayer);
        this->_networkLogicLayer->registerAbstractionLayer(weakAL);

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
    int seconds = _nllUpdateTimer->interval() / 1000;
    emit updateNLL( seconds );
}
