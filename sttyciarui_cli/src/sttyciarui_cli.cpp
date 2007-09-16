#include "sttyciarui_cli.hh"
#include "sttyciarui_cli_main.hh"

SttyciarCLI::SttyciarCLI()
{
    _mainUI.reset( new SttyciarCLIMain );
    connect(_mainUI.get(), SIGNAL(redraw()), this, SLOT(showMain()));

    connect(_mainUI.get(), SIGNAL(startSttyciar(QString)),
            this, SIGNAL( startSttyciar(QString) ));

    connect(_mainUI.get(), SIGNAL(startSttyciar(int)),
            this, SLOT(showStatistics()));

    connect(_mainUI.get(), SIGNAL(exit()), this, SLOT(exit()));
}

void SttyciarCLI::updateStatistics()
{

}

void SttyciarCLI::exit()
{
    disconnect(_mainUI.get(), SIGNAL(redraw()), this, SLOT(showMain()));

    disconnect(_mainUI.get(), SIGNAL(startSttyciar(QString)),
            this, SIGNAL( startSttyciar(QString) ));

    disconnect(_mainUI.get(), SIGNAL(startSttyciar(QString)),
            this, SLOT(showStatistics()));

    disconnect(_mainUI.get(), SIGNAL(exit()), this, SLOT(exit()));

    _mainUI.reset();

    emit exitSignal();
}

void SttyciarCLI::showMain()
{
    _mainUI->draw();
}

void SttyciarCLI::showStatistics()
{

}

