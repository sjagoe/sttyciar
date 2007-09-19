#include <QApplication>
#include <QObject>

#include "sttyciarui_gui.hh"
#include "sttyciarui_gui_main.hh"
#include "sttyciarui_gui_statistics.hh"

SttyciarGUI::SttyciarGUI()
{
    _mainUI.reset( new SttyciarGUIMain );

    connect( _mainUI.get(), SIGNAL(startSttyciar(short)), this, SLOT(startSttyciar(short)) );

    _mainUI->show();
}

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    SttyciarGUIStatistics ui;
    QObject::connect( &ui, SIGNAL(exit()), &app, SLOT(quit()) );

    ui.show();

    return app.exec();
}
