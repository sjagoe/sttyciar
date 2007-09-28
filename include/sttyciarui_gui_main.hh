#ifndef __STTYCIARUI_GUI_MAIN_HH__
#define __STTYCIARUI_GUI_MAIN_HH__

#include <QMainWindow>
#include <QList>

#include <boost/shared_ptr.hpp>

//#include "ui_sttyciar_gui_main.h"

//!Forward decleration of the GUI Form (Ui namespace from Qt form generator).
namespace Ui
{
    class FormSttyciarGUIMain;
};

using boost::shared_ptr;

class Device;
class QTreeWidget;

/*!
The main window if the Sttyciar GUI, allowing users to select devices to bind
to the system, and the type of network hardware to implement.

\author Simon Jagoe
*/
class SttyciarGUIMain: public QMainWindow
{
    Q_OBJECT
    public:
        SttyciarGUIMain(QWidget* parent = 0);

        void setDevices( const QList<shared_ptr<Device> >& devices );
        void setNetworkDevices( QMap<int, QString> networkDevices );

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
        void startSttyciar(QString deviceType, shared_ptr<QStringList> devices);
        void exit();
};

#endif
