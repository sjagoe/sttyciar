//#include <iostream>
//#include <QApplication>
#include <QObject>

#include "sttyciarui_gui.hh"

SttyciarGUI::SttyciarGUI(QMap<int, QString>& networkDevices)
{
    _availableNetworkDevices = networkDevices;
    _mainUI.reset( new SttyciarGUIMain );

    _mainUI->setNetworkDevices( networkDevices );

    _statisticsUI.reset( new SttyciarGUIStatistics );

    connect( _mainUI.get(),
        SIGNAL(startSttyciar(QString, shared_ptr<QStringList>)),
        this, SLOT(startSttyciarSlot(QString, shared_ptr<QStringList>)) );

    connect( _mainUI.get(), SIGNAL(exit()), this, SLOT(exit()) );

    connect( _statisticsUI.get(), SIGNAL(exit()), this, SLOT(exit()) );

    connect( _statisticsUI.get(), SIGNAL(stopSttyciar()),
        this, SLOT(stopSttyciarSlot()) );

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

void SttyciarGUI::startSttyciarSlot(QString deviceType, shared_ptr<QStringList> devices)
{
    emit startSttyciar(deviceType, devices);
}

void SttyciarGUI::stopSttyciarSlot()
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
