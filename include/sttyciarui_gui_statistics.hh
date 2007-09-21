#ifndef __STTYCIARUI_GUI_STATISTICS_HH__
#define __STTYCIARUI_GUI_STATISTICS_HH__

#include <iostream>

#include <QMainWindow>
#include <QPushButton>
#include <QWidget>
#include <QTabWidget>
#include <QGroupBox>
#include <QTableWidget>
#include <QLabel>
#include <QLineEdit>

class QHBoxLayout;

//#include "ui_textstatisticswidget.h"

class SttyciarGUIStatistics: public QMainWindow
{
    Q_OBJECT
    public:
        SttyciarGUIStatistics(QWidget* parent = 0);

    private:
        void setupTabWidget();
        void setupRates();
        QHBoxLayout* setupButtons();

        QTabWidget* _tabs;

//        QGroupBox* _grpTextualLoad;
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
