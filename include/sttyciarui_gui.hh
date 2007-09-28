#ifndef __STTYCIARUI_GUI_HH__
#define __STTYCIARUI_GUI_HH__

//#include <iostream>

#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>

#include "sttyciarui_common.hh"
#include "sttyciarui_gui_main.hh"
#include "sttyciarui_gui_statistics.hh"

#include "device.hh"

using boost::scoped_ptr;
using boost::shared_ptr;

/*!
Subclass of SttyciarUI providing a Qt GUI interface to Sttyciar.

\author Simon Jagoe
*/
class SttyciarGUI: public SttyciarUI
{
    Q_OBJECT
    public:
        /*!
        Construct the GUI with a map of available system types, and a
        corresponding index value.

        \param networkDevices QMap containing a Key of the index of a device,
        and Value of a description/name string.
        */
        SttyciarGUI(QMap<int, QString>& networkDevices);

    public slots:
        /*!
        Implement the sttyciarRunning() slot in \link sttyciarui_common.hh
        */
        void sttyciarRunning();

        /*!
        Implement the sttyciarStopped() slot in \link sttyciarui_common.hh
        */
        void sttyciarStopped();

        /*!
        Implement the updateStatistics() slot in \link sttyciarui_common.hh
        */
        void updateStatistics( shared_ptr<Statistics> stats );

        /*!
        Implement the receiveDevices() slot in \link sttyciarui_common.hh
        */
        void receiveDevices( const QList<shared_ptr<Device> >& devices );

        /*!
        Implement the receiveActivatedDevices() slot in
        \link sttyciarui_common.hh
        */
        void receiveActivatedDevices(
            const QList<shared_ptr<Device> >& devices );

    protected slots:
        /*!
        Implement the exit() slot in \link sttyciarui_common.hh
        */
        void exit();

        /*!
        Slot to be initiated by the main user interface to start Sttyciar.

        This emits the startSttyciar signal specified in the interface.
        */
        void startSttyciarSlot(QString deviceType, shared_ptr<QStringList> devices);

        /*!
        Slot to be initiated by the main user interface to stop Sttyciar.

        This emits the stopSttyciar signal specified in the interface.
        */
        void stopSttyciarSlot();

    private:
        scoped_ptr<SttyciarGUIMain> _mainUI; //! Pointer to the SttyciarGUIMain object that displays the main form.
        scoped_ptr<SttyciarGUIStatistics> _statisticsUI; //! Pointer to the SttyciarGUIStatistics object that displays the statistics form.
        QMap<int, QString> _availableNetworkDevices; //! Available network devices to be implemented.
};

#endif
