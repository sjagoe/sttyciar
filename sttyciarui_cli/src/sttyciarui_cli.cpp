#include "sttyciarui_cli.hh"
#include "sttyciarui_cli_main.hh"
#include "sttyciarui_cli_statistics.hh"

SttyciarCLI::SttyciarCLI()
{
    _statisticsVisible = false;

    // main UI stuff

    _mainUI.reset( new SttyciarCLIMain );
    // redraw
    connect(_mainUI.get(), SIGNAL(redraw()), this, SLOT(showMain()));
    // start
    connect(_mainUI.get(), SIGNAL(startSttyciar(QString)),
            this, SIGNAL( startSttyciar(QString) ));
    // start ( show statistics view )
    connect(_mainUI.get(), SIGNAL(startSttyciar(QString)),
            this, SLOT(showStatistics()));
    // exit
    connect(_mainUI.get(), SIGNAL(exit()), this, SLOT(exit()));

    // statistics UI stuff

    _statisticsUI.reset(new SttyciarCLIStatistics);

    // exit
    connect( _statisticsUI.get(), SIGNAL(exit()), this, SLOT(exit()));
    // redraw
    connect( _statisticsUI.get(), SIGNAL(redraw()),
            this, SLOT( showStatistics() ));
    // stop
    connect( _statisticsUI.get(), SIGNAL( stopSttyciar() ),
            this, SIGNAL( stopSignal() ) );
    //stop (show main view)
    connect ( _statisticsUI.get(), SIGNAL( stopSttyciar() ),
            this, SLOT( showMain() ) );

}

void SttyciarCLI::updateStatistics()
{
    if (_statisticsVisible)
    {
        //_statisticsUI->draw();
    }
}

void SttyciarCLI::exit()
{
    disconnect(_mainUI.get(), SIGNAL(redraw()), this, SLOT(showMain()));

    disconnect(_mainUI.get(), SIGNAL(startSttyciar(QString)),
            this, SIGNAL( startSttyciar(QString) ));

    disconnect(_mainUI.get(), SIGNAL(startSttyciar(QString)),
            this, SLOT(showStatistics()));

    disconnect(_mainUI.get(), SIGNAL(exit()), this, SLOT(exit()));

    disconnect( _statisticsUI.get(), SIGNAL(exit()), this, SLOT(exit()));

    disconnect( _statisticsUI.get(), SIGNAL(redraw()),
            this, SLOT( showStatistics() ));

    disconnect( _statisticsUI.get(), SIGNAL( stopSttyciar() ),
            this, SIGNAL( stopSignal() ) );

    disconnect ( _statisticsUI.get(), SIGNAL( stopSttyciar() ),
            this, SLOT( showMain() ) );

    _mainUI.reset();
    _statisticsUI.reset();

    emit exitSignal();
}

void SttyciarCLI::showMain()
{
    _statisticsVisible = false;
    _mainUI->draw();
}

void SttyciarCLI::showStatistics()
{
    _statisticsVisible = true;
    _statisticsUI->draw();
}
