//#include <iostream>
//#include <QApplication>
#include <QObject>
#include <QStringList>

#include "sttyciarui_gui.hh"

SttyciarGUI::SttyciarGUI(QMap<int, QString>& networkDevices)
{
    _availableNetworkDevices = networkDevices;
    _mainUI.reset( new SttyciarGUIMain );

    _mainUI->setNetworkDevices( networkDevices );

    _statisticsUI.reset( new SttyciarGUIStatistics(networkDevices) );

    connect( _mainUI.get(),
        SIGNAL(startSttyciar(QString, shared_ptr<QStringList>, QString)),
        this, SLOT(startSttyciarSlot(QString, shared_ptr<QStringList>, QString)) );

    connect( _mainUI.get(), SIGNAL(exit()), this, SLOT(exit()) );

    connect( _statisticsUI.get(), SIGNAL(exit()), this, SLOT(exit()) );

    connect( _statisticsUI.get(), SIGNAL(stopSttyciar()),
        this, SLOT(stopSttyciarSlot()) );

    connect( _statisticsUI.get(), SIGNAL( restartSttyciar(const QString&,
                                            const shared_ptr<QStringList>&,
                                            const QString&) ),
            this, SLOT( restartSttyciarSlot(const QString&,
                                            const shared_ptr<QStringList>&,
                                            const QString&) ) );

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

void SttyciarGUI::updateStatistics( shared_ptr<Statistics>& stats )
{
    _statisticsUI->updateStatistics( stats );
}

void SttyciarGUI::receiveDevices(
    const QList<shared_ptr<Device> >& devices )
{
    _mainUI->setDevices( devices );
}

void SttyciarGUI::receiveActivatedDevices(
    const QList<shared_ptr<Device> >& devices )
{
    _statisticsUI->receiveActivatedDevices( devices, this->_deviceType,
        this->_deviceList, this->_dumpFile );
}

void SttyciarGUI::exit()
{
    emit exitSttyciar();
}

void SttyciarGUI::startSttyciarSlot(QString deviceType, shared_ptr<QStringList> devices, QString dumpFile)
{
    this->_deviceList = devices;
    this->_deviceType = deviceType;
    this->_dumpFile = dumpFile;
    emit startSttyciar(deviceType, devices, dumpFile);
}

void SttyciarGUI::stopSttyciarSlot()
{
    emit stopSttyciar();
}

void SttyciarGUI::restartSttyciarSlot(const QString& deviceType,
    const shared_ptr<QStringList>& deviceList,
    const QString& dumpFile)
{
    this->_deviceList = deviceList;
    this->_deviceType = deviceType;
    this->_dumpFile = dumpFile;
    emit restartSttyciar( deviceType, deviceList, dumpFile );
}
