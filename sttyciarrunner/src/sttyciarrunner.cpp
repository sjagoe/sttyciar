#include "sttyciarrunner.hh"

#include "sttyciarui_cli.hh"


#include "nllhub.hh"

const short SttyciarUI::HUB_TYPE;

SttyciarRunner::SttyciarRunner()
{
    _ui.reset( new SttyciarCLI );
}

void SttyciarRunner::startSttyciar(short deviceType)
{
    if ( deviceType == SttyciarUI::HUB_TYPE )
    {

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
