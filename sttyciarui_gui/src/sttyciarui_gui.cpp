#include <QApplication>

#include "sttyciarui_gui.hh"
#include "sttyciarui_gui_main.hh"


SttyciarGUI::SttyciarGUI()
{
    _mainUI.reset( new SttyciarGUIMain );

    connect( _mainUI.get(), SIGNAL(startSttyciar(short)), this, SLOT(startSttyciar(short)) );

    _mainUI->show();
}

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    SttyciarGUI ui;

    return app.exec();
}
