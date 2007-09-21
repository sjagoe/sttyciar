//#include <iostream>

#include "abstractionlayer.hh"
#include "alnetworklistener.hh"
#include "networklogiclayer.hh"

#include "sttyciarrunner.hh"
#include "sttyciarui_gui.hh"
#include "nllhub.hh"

const short SttyciarUI::HUB_TYPE;

const int SttyciarRunner::PACKET_CAPTURE_SIZE;
const int SttyciarRunner::PCAP_READ_TIMEOUT;

SttyciarRunner::SttyciarRunner()
{
    _abstractionLayer.reset( new AbstractionLayer );
    _ui.reset( new SttyciarGUI );
    connect( _ui.get(), SIGNAL(exitSttyciar()), this, SLOT(exitSttyciar()));

    connect( _ui.get(),
        SIGNAL( startSttyciar(short, shared_ptr<QStringList>) ),
        this, SLOT( startSttyciar(short, shared_ptr<QStringList>) ) );

    connect( _ui.get(), SIGNAL( stopSttyciar() ), this, SLOT( stopSttyciar() ) );

    _ui->receiveDevices( _abstractionLayer->getDevices() );
}

void SttyciarRunner::startSttyciar(short deviceType,
    shared_ptr<QStringList> devices)
{
    switch ( deviceType )
    {
        case SttyciarUI::HUB_TYPE:
        {
            _networkLogicLayer.reset( new NLLHub );
            weak_ptr<ALNetworkListener> weakNLL(_networkLogicLayer);
            _abstractionLayer->registerNLL(weakNLL);
            weak_ptr<AbstractionLayer> weakAL(_abstractionLayer);
            _networkLogicLayer->registerAbstractionLayer(weakAL);

            _abstractionLayer->activateDevices( devices );

            _networkLogicLayer->start();
            _abstractionLayer->startListening(PACKET_CAPTURE_SIZE,
                                              PCAP_READ_TIMEOUT);
            _ui->sttyciarRunning();
            break;
        }
    }
}

void SttyciarRunner::stopSttyciar()
{
    // stop the abstractionlayer from listeneing for packets
    _abstractionLayer->stopListening();
    // stop the NLL from processing packets
    _networkLogicLayer->exitNow();
    _networkLogicLayer->wait();
    // destroy the AL and NLL objects
    _networkLogicLayer.reset();
    // notify the UI
    _ui->sttyciarStopped();
}

void SttyciarRunner::exitSttyciar()
{
    stopSttyciar();
    emit exit();
//    _abstractionLayer.reset();
//    _ui.reset();
}
