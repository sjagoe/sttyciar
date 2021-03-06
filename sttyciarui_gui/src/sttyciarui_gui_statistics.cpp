//#include <iostream>

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>

#include <QPushButton>
#include <QWidget>
#include <QTabWidget>
#include <QGroupBox>
#include <QTableWidget>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QStringList>

#include "sttyciarui_gui_statistics.hh"

#include "loadcanvas.hh"
#include "loadtable.hh"

SttyciarGUIStatistics::SttyciarGUIStatistics( QMap<int, QString> networkDevices, QWidget* parent )
    : QMainWindow( parent )
{
    setupDeviceSelection(networkDevices);
    setupTabWidget();
    setupRates();

    QHBoxLayout* hlayout = setupButtons();

    QVBoxLayout* vlayout = new QVBoxLayout;
    vlayout->addWidget( _grpChangeDevice );
    vlayout->addWidget( _tabs );
    vlayout->addWidget( _grpRates );
    vlayout->addLayout(hlayout);

    _centralWidget = new QWidget;

    _centralWidget->setLayout(vlayout);

    this->setCentralWidget( _centralWidget );

    connect( _exitButton, SIGNAL( clicked() ), this, SIGNAL( exit() ) );
    connect( _stopButton, SIGNAL( clicked() ),
            this, SIGNAL( stopSttyciar() ) );

    this->setWindowTitle( "Sttyciar Traffic Statistics" );
}

void SttyciarGUIStatistics::receiveActivatedDevices(
    const QList<shared_ptr<Device> >& devices, const QString& deviceType,
    const shared_ptr<QStringList>& deviceList,
    const QString& dumpFile )
{
    this->_devices = deviceList;
    this->_graphLoad->setLabels( devices );
    this->_tblLoad->setLabels( devices );
    this->_tblPackets->setLabels( devices );
    this->_tblBytesPerSecond->setLabels( devices );
    int i = this->_comboChangeDevice->findText( deviceType );
    this->_comboChangeDevice->setCurrentIndex(i);
    this->_dumpFile = dumpFile;
}

void SttyciarGUIStatistics::updateStatistics( shared_ptr<Statistics> stats )
{
    if ( this->_statistics.get() != stats.get() )
    {
        this->_statistics = stats;

        // update stats
        if ( this->_statistics.get() != 0 )
        {
            this->_graphLoad->updateStatistics( this->_statistics );
            this->_tblLoad->updateStatistics( this->_statistics->getTrafficPercentageTable() );
            this->_tblPackets->updateStatistics( this->_statistics->getTrafficAmtPacketsTable() );
            this->_tblBytesPerSecond->updateStatistics( this->_statistics->getTrafficAmtBytesPerSecondTable() );

            QString temp = QString("%1").arg( this->_statistics->getPacketsPerSecond() );
            this->_edtPacketsPerSecond->setText( temp );

            double kbytes = this->_statistics->getBytesPerSecond();

            temp = QString( "%1" ).arg( kbytes );
            this->_edtBytesPerSecond->setText( temp );

            kbytes /= 1024;

            temp = QString( "%1" ).arg( kbytes );
            this->_edtKBytesPerSecond->setText( temp );

            temp = QString( "%1" ).arg(this->_statistics->getAwaitingDumpedPackets());
            this->_edtDumpBuffer->setText( temp );
        }
    }
}

void SttyciarGUIStatistics::setupDeviceSelection(QMap<int, QString> networkDevices)
{
    this->_grpChangeDevice = new QGroupBox( QString("Change Device Type") );
    this->_lblChangeDevice = new QLabel( QString("Device Type") );
    this->_comboChangeDevice = new QComboBox;

    QHBoxLayout* l = new QHBoxLayout;
    l->addWidget(this->_lblChangeDevice);
    l->addWidget(this->_comboChangeDevice);
    l->setStretchFactor(this->_comboChangeDevice, 1);
    this->_grpChangeDevice->setLayout(l);

    for (int i = 0; i < networkDevices.size(); i++)
    {
        if (!networkDevices[i].isEmpty())
        {
            this->_comboChangeDevice->addItem( networkDevices[i] );
        }
    }

    connect( this->_comboChangeDevice, SIGNAL(activated(const QString&)),
        this, SLOT(deviceChanged(const QString&)));
}

void SttyciarGUIStatistics::setupTabWidget()
{
    _tabs = new QTabWidget;

    _graphLoad = new LoadCanvas;

//    _grpTextualLoad = new QGroupBox( QString( "Load Balance" ) );
    //_tblTextualLoad = new QTableWidget;
    _tblLoad = new LoadTable(true); // The _tblLoad displays a percentage
    _tblPackets = new LoadTable(false, 1000);
    _tblBytesPerSecond = new LoadTable(false, 1024);

    _tabs->addTab( _graphLoad, QString( "Load Balance (Graphical)" ) );
//    _tabs->addTab( _tblTextualLoad, QString( "Load Balance (Table)" ) );
    _tabs->addTab( _tblLoad, QString( "Load Balance (Table)" ) );
    _tabs->addTab( _tblPackets, QString( "Packet Count" ) );
    _tabs->addTab( _tblBytesPerSecond, QString( "Bytes Per Second" ) );
}

void SttyciarGUIStatistics::setupRates()
{
    this->_grpRates = new QGroupBox( QString("Data Rates") );

    this->_lblPacketsPerSecond = new QLabel( QString("Packets/Second:") );
    this->_lblBytesPerSecond = new QLabel( QString("Bytes/Second:") );
    this->_lblKBytesPerSecond = new QLabel( QString( "Kilobytes/Second:" ) );

    this->_edtPacketsPerSecond = new QLineEdit;
    this->_edtPacketsPerSecond->setReadOnly(true);
    this->_edtBytesPerSecond = new QLineEdit;
    this->_edtBytesPerSecond->setReadOnly(true);
    this->_edtKBytesPerSecond = new QLineEdit;
    this->_edtKBytesPerSecond->setReadOnly(true);

    this->_lblPacketsPerSecond->setBuddy( this->_edtPacketsPerSecond );
    this->_lblBytesPerSecond->setBuddy( this->_edtBytesPerSecond );
    this->_lblKBytesPerSecond->setBuddy( this->_edtKBytesPerSecond );

    QGridLayout* layout = new QGridLayout;

    layout->addWidget( this->_lblPacketsPerSecond, 0, 0 );
    layout->addWidget( this->_edtPacketsPerSecond, 1, 0 );
    layout->addWidget( this->_lblBytesPerSecond, 0, 1 );
    layout->addWidget( this->_edtBytesPerSecond, 1, 1 );
    layout->addWidget( this->_lblKBytesPerSecond, 0, 2 );
    layout->addWidget( this->_edtKBytesPerSecond, 1, 2 );

    _grpRates->setLayout( layout );
}

QHBoxLayout* SttyciarGUIStatistics::setupButtons()
{
    _lblDumpBuffer = new QLabel( QString( "Dump Buffer:" ) );
    _edtDumpBuffer = new QLineEdit;
    _lblDumpBuffer->setBuddy(_edtDumpBuffer);
    _edtDumpBuffer->setReadOnly(true);

    _exitButton = new QPushButton( QString( "&Exit" ) );
    _stopButton = new QPushButton( QString( "&Stop" ) );

    QHBoxLayout* hlayout = new QHBoxLayout;
    hlayout->addWidget( _lblDumpBuffer );
    hlayout->addWidget( _edtDumpBuffer );
    hlayout->addStretch();
    hlayout->addWidget(_stopButton);
    hlayout->addWidget(_exitButton);

    return hlayout;
}

void SttyciarGUIStatistics::deviceChanged(const QString& text)
{
    emit restartSttyciar( text, this->_devices, this->_dumpFile );
}
