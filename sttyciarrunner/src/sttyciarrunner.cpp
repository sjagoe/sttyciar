#include <iostream>

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
    connect( _ui.get(), SIGNAL(exitSttyciar()), this, SIGNAL(exit()));
    _ui->receiveDevices( _abstractionLayer->getDevices() );
}

void SttyciarRunner::startSttyciar(short deviceType)
{
    if ( deviceType == SttyciarUI::HUB_TYPE )
    {
        _networkLogicLayer.reset( new NLLHub );
        weak_ptr<ALNetworkListener> weakNLL(_networkLogicLayer);
        _abstractionLayer->registerNLL(weakNLL);
        weak_ptr<AbstractionLayer> weakAL(_abstractionLayer);
        _networkLogicLayer->registerAbstractionLayer(weakAL);
        _networkLogicLayer->start();
        _abstractionLayer->startListening(PACKET_CAPTURE_SIZE,
                                          PCAP_READ_TIMEOUT);
    }
}

void SttyciarRunner::stopSttyciar()
{
    // stop the abstractionlayer from listeneing for packets
    _abstractionLayer->stopListening();
    // stop the NLL from processing packets
    _networkLogicLayer->exitNow();
    // destroy the AL and NLL objects
    _networkLogicLayer.reset();
}

void SttyciarRunner::exitSttyciar()
{
    stopSttyciar();
    _abstractionLayer.reset();
    _ui.reset();
}
