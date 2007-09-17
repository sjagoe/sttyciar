#include "sttyciarrunner.hh"

#include "sttyciarui_cli.hh"


#include "nllhub.hh"

const short SttyciarUI::HUB_TYPE;

const int SttyciarRunner::PACKET_CAPTURE_SIZE;
const int SttyciarRunner::PCAP_READ_TIMEOUT;

SttyciarRunner::SttyciarRunner()
{
    _ui.reset( new SttyciarCLI );
}

void SttyciarRunner::startSttyciar(short deviceType)
{
    _abstractionLayer.reset( new AbstractionLayer );

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
    _abstractionLayer.reset();
    _networkLogicLayer.reset();
}

void SttyciarRunner::exitSttyciar()
{
    stopSttyciar();
    _ui.reset();
}
