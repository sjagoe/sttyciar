#include <QApplication>
#include <QObject>

#include "sttyciarui_gui.hh"

SttyciarGUI::SttyciarGUI()
{
    _mainUI.reset( new SttyciarGUIMain );
    _statisticsUI.reset( new SttyciarGUIStatistics );

    connect( _mainUI.get(), SIGNAL(startSttyciar(short)), this, SLOT(startSttyciar(short)) );
    connect( _mainUI.get(), SIGNAL(exit()), this, SLOT(exit()) );
    connect( _statisticsUI.get(), SIGNAL(exit()), this, SLOT(exit()) );

    _mainUI->show();
}

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    SttyciarGUI ui;
    QObject::connect( &ui, SIGNAL(exitSttyciar()), &app, SLOT(quit()) );

    return app.exec();
}
