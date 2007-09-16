#include "sttyciarrunner.hh"

#include "sttyciarui_cli.hh"

SttyciarRunner::SttyciarRunner()
{
    _ui.reset( new SttyciarCLI );
}

void SttyciarRunner::startSttyciar(QString deviceType)
{

}

void SttyciarRunner::stopSttyciar()
{
    _networkLogicLayer->exitNow();

}

void SttyciarRunner::exitSttyciar()
{
    stopSttyciar();
    _ui.reset();
}
