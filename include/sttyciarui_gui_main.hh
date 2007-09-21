#ifndef __STTYCIARUI_GUI_MAIN_HH__
#define __STTYCIARUI_GUI_MAIN_HH__

#include <QMainWindow>
#include <QList>

#include <boost/shared_ptr.hpp>

//#include "ui_sttyciar_gui_main.h"
namespace Ui
{
    class FormSttyciarGUIMain;
};

using boost::shared_ptr;

class Device;
class QTreeWidget;

class SttyciarGUIMain: public QMainWindow
{
    Q_OBJECT
    public:
        SttyciarGUIMain(QWidget* parent = 0);

        void setDevices( const QList<shared_ptr<Device> >& devices );

    private:
        Ui::FormSttyciarGUIMain* _ui;

    private slots:
        void on_btnStart_clicked();

        void on_btnAddAllDevices_clicked();

        void on_btnAddDevice_clicked();

        void on_btnRemoveDevice_clicked();

        void on_btnRemoveAllDevices_clicked();

        void on_btnExit_clicked();

        void moveAllDevices(QTreeWidget* sourceInterfaceTree,
            QTreeWidget* destinationInterfaceTree);
        void moveDevice(QTreeWidget* sourceInterfaceTree,
            QTreeWidget* destinationInterfaceTree);

    signals:
        void startSttyciar(short deviceType, shared_ptr<QStringList> devices);
        void exit();
};

#endif
