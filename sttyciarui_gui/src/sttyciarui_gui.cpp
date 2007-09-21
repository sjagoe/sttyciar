//#include <iostream>
//#include <QApplication>
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

void SttyciarGUI::sttyciarRunning()
{
    _mainUI->hide();
    _statisticsUI->show();
}

void SttyciarGUI::sttyciarStopped()
{
    _statisticsUI->hide();
    _mainUI->show();
}

void SttyciarGUI::updateStatistics()
{

}

void SttyciarGUI::receiveDevices(
    const QList<shared_ptr<Device> >& devices )
{
    _mainUI->setDevices( devices );
}

void SttyciarGUI::exit()
{
    emit exitSttyciar();
}

void SttyciarGUI::startSttyciar(short deviceType)
{
    emit startSttyciar(deviceType);
}

void SttyciarGUI::stopSttyciar()
{
    emit stopSttyciar();
}

//int main(int argc, char* argv[])
//{
//    QApplication app(argc, argv);
//
//    SttyciarGUI ui;
//    QObject::connect( &ui, SIGNAL(exitSttyciar()), &app, SLOT(quit()) );
//
//    return app.exec();
//}
