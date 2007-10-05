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
        /*!
        Default constructor to set up the UI layout. The \a parent parameter is
        passed to the \c QMainWindow constructor.

        \param parent QWidget parent of the object, passed to the \c QMainWindow
        constructor.
        */
        SttyciarGUIMain(QWidget* parent = 0);

        /*!
        Pass the UI a list of Device objects that will be used to display and
        select the Devices to bind to the Network Device/System.

        \param devices A \c QList of \c Device \c shared_ptrs.
        */
        void setDevices( const QList<shared_ptr<Device> >& devices );

        /*!
        Pass the UI a \c QMap of Network Devices (Network Systems, such as Hub),
        and a unique integer identifier, used to allow the user to select a
        device type to use.

        \param networkDevices The \c QMap of device types that can be chosen
        from.
        */
        void setNetworkDevices( QMap<int, QString> networkDevices );

    private:
        Ui::FormSttyciarGUIMain* _ui; //! The actual GUI form, designed in Qt Designer.

    private slots:
        /*!
        Auto-connection slot for the clicked() signal of the Start button
        (btnStart).
        */
        void on_btnStart_clicked();

        /*!
        Auto-connection slot for the clicked() signal of the Add All Devices
        button (btnAddAllDevices).
        */
        void on_btnAddAllDevices_clicked();

        /*!
        Auto-connection slot for the clicked() signal of the Add Device button
        (btnAddDevice).
        */
        void on_btnAddDevice_clicked();

        /*!
        Auto-connection slot for the clicked() signal of the Remove Device
        button (btnRemoveDevice).
        */
        void on_btnRemoveDevice_clicked();

        /*!
        Auto-connection slot for the clicked() signal of the Remove All Devices
        button (btnRemoveAllDevices).
        */
        void on_btnRemoveAllDevices_clicked();

        /*!
        Auto-connection slot for the clicked() signal of the Exit button
        (btnExit).
        */
        void on_btnExit_clicked();

        /*!
        A method used to catch when the checkbox to enable/disable dump to file
        has been toggled.
        */
        void on_chkEnableDump_stateChanged();

        /*!
        A method to handle when a user clicks on the browse button.
        */
        void on_btnBrowseDump_clicked();

        /*!
        A method used to move all devices from one tree-widget to another
        */
        void moveAllDevices(QTreeWidget* sourceInterfaceTree,
            QTreeWidget* destinationInterfaceTree);

        /*!
        A method used to move one device from one tree-widget to another
        */
        void moveDevice(QTreeWidget* sourceInterfaceTree,
            QTreeWidget* destinationInterfaceTree);

        /*!
        When a user double clicks on an item in the Available Interfaces tree,
        the device will be moved to the Used Interfaces tree (i.e. it will be
        activated when the system is started).
        */
        void on_treeAvailableInterfaces_itemDoubleClicked();

        /*!
        When a user double clicks on an item in the Used Interfaces tree,
        the device will be moved to the Available Interfaces tree (i.e. it will
        not be activated when the system is started).
        */
        void on_treeUsedInterfaces_itemDoubleClicked();

    signals:
        /*!
        Signal emitted when the Start Device button is clicked to signal the
        SttyciarRunner to start Sttyciar.
        */
        void startSttyciar(QString deviceType, shared_ptr<QStringList> devices,
            QString dumpFile);

        /*!
        Signal emitted when the Exit button is clicked, signalling the
        SttyciarRunner to exit the application.
        */
        void exit();
};

#endif
