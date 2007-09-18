#ifndef __STTYCIARUI_GUI_MAIN_HH__
#define __STTYCIARUI_GUI_MAIN_HH__

#include <QMainWindow>

#include "ui_main.h"

class SttyciarGUIMain: public QMainWindow
{
    Q_OBJECT
    public:
        SttyciarGUIMain();

    private:
        Ui::FormSttyciarGUIMain _ui;

    private slots:
        void on_btnStart_clicked();

        void on_btnAddAllDevices_clicked();

        void on_btnAddDevice_clicked();

        void on_btnRemoveDevice_clicked();

        void on_btnRemoveAllDevices_clicked();

        void moveAllDevices(QTreeWidget* sourceInterfaceTree,
            QTreeWidget* destinationInterfaceTree);
        void moveDevice(QTreeWidget* sourceInterfaceTree,
            QTreeWidget* destinationInterfaceTree);

    signals:
        void startSttyciar(short deviceType);
};

#endif
