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

#include "sttyciarui_gui_statistics.hh"

#include "loadcanvas.hh"

SttyciarGUIStatistics::SttyciarGUIStatistics( QWidget* parent )
    : QMainWindow( parent )
{
    setupTabWidget();
    setupRates();

    QHBoxLayout* hlayout = setupButtons();

    QVBoxLayout* vlayout = new QVBoxLayout;
    vlayout->addWidget( _tabs );
    vlayout->addWidget( _grpRates );
    vlayout->addLayout(hlayout);

    _centralWidget = new QWidget;

    _centralWidget->setLayout(vlayout);

    this->setCentralWidget( _centralWidget );

    connect( _exitButton, SIGNAL( clicked() ), this, SIGNAL( exit() ) );
    connect( _stopButton, SIGNAL( clicked() ),
            this, SIGNAL( stopSttyciar() ) );
}

void SttyciarGUIStatistics::receiveActivatedDevices(
    const QList<shared_ptr<Device> >& devices )
{
    this->_graphLoad->setLabels( devices );
}

void SttyciarGUIStatistics::updateStatistics( shared_ptr<Statistics> stats )
{
    _graphLoad->updateStatistics( stats );
}

void SttyciarGUIStatistics::setupTabWidget()
{
    _tabs = new QTabWidget;

    _graphLoad = new LoadCanvas;

//    _grpTextualLoad = new QGroupBox( QString( "Load Balance" ) );
    _tblTextualLoad = new QTableWidget;

    _tabs->addTab( _graphLoad, QString( "Load Balance (Graphical)" ) );
    _tabs->addTab( _tblTextualLoad, QString( "Load Balance (Table)" ) );
}

void SttyciarGUIStatistics::setupRates()
{
    _grpRates = new QGroupBox( QString("Data Rates") );

    _lblPacketsPerSecond = new QLabel( QString("Packets/Second:") );
    _lblBytesPerSecond = new QLabel( QString("Bytes/Second:") );

    _edtPacketsPerSecond = new QLineEdit;
    _edtPacketsPerSecond->setReadOnly(true);
    _edtBytesPerSecond = new QLineEdit;
    _edtBytesPerSecond->setReadOnly(true);

    _lblPacketsPerSecond->setBuddy( _edtPacketsPerSecond );
    _lblBytesPerSecond->setBuddy( _edtBytesPerSecond );

    QGridLayout* layout = new QGridLayout;

    layout->addWidget( _lblPacketsPerSecond, 0, 0 );
    layout->addWidget( _edtPacketsPerSecond, 1, 0 );
    layout->addWidget( _lblBytesPerSecond, 0, 1 );
    layout->addWidget( _edtBytesPerSecond, 1, 1 );

    _grpRates->setLayout( layout );
}

QHBoxLayout* SttyciarGUIStatistics::setupButtons()
{
    _exitButton = new QPushButton( QString( "&Exit" ) );
    _stopButton = new QPushButton( QString( "&Stop" ) );

    QHBoxLayout* hlayout = new QHBoxLayout;
    hlayout->addStretch();
    hlayout->addWidget(_stopButton);
    hlayout->addWidget(_exitButton);

    return hlayout;
}
