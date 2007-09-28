#ifndef __STTYCIARUI_GUI_STATISTICS_HH__
#define __STTYCIARUI_GUI_STATISTICS_HH__

//#include <iostream>

#include <QMainWindow>

#include <boost/shared_ptr.hpp>

using boost::shared_ptr;

// Qt Forward Declerations
class QHBoxLayout;
class QPushButton;
class QWidget;
class QTabWidget;
class QGroupBox;
class QTableWidget;
class QLabel;
class QLineEdit;

// Local Forward Declerations
class LoadCanvas;
class Device;
class Statistics;

class SttyciarGUIStatistics: public QMainWindow
{
    Q_OBJECT
    public:
        SttyciarGUIStatistics(QWidget* parent = 0);

    public slots:
        void receiveActivatedDevices(
            const QList<shared_ptr<Device> >& devices );

        void updateStatistics( shared_ptr<Statistics> stats );

    private:
        void setupTabWidget();
        void setupRates();
        QHBoxLayout* setupButtons();

        QTabWidget* _tabs;

        LoadCanvas* _graphLoad;
        QTableWidget* _tblTextualLoad;

        QGroupBox* _grpRates;
        QLabel* _lblPacketsPerSecond;
        QLineEdit* _edtPacketsPerSecond;
        QLabel* _lblBytesPerSecond;
        QLineEdit* _edtBytesPerSecond;

        QPushButton* _exitButton;
        QPushButton* _stopButton;

        QWidget* _centralWidget;

    signals:
        void exit();
        void stopSttyciar();
};

#endif
