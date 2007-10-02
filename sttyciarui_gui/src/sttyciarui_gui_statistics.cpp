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
    if ( this->_statistics.get() != stats.get() )
    {
        this->_statistics = stats;
        this->_graphLoad->updateStatistics( this->_statistics );
//        this->_tblLoad->updateStatistics( this->_statistics );

        // update stats
        if ( this->_statistics.get() != 0 )
        {
            QString temp = QString("%1").arg( this->_statistics->getPacketsPerSecond() );
            this->_edtPacketsPerSecond->setText( temp );

            double kbytes = this->_statistics->getBytesPerSecond();

            temp = QString( "%1" ).arg( kbytes );
            this->_edtBytesPerSecond->setText( temp );

            kbytes /= 1024;

            temp = QString( "%1" ).arg( kbytes );
            this->_edtKBytesPerSecond->setText( temp );
        }
    }
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
    _exitButton = new QPushButton( QString( "&Exit" ) );
    _stopButton = new QPushButton( QString( "&Stop" ) );

    QHBoxLayout* hlayout = new QHBoxLayout;
    hlayout->addStretch();
    hlayout->addWidget(_stopButton);
    hlayout->addWidget(_exitButton);

    return hlayout;
}
