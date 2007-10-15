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

class QStringList;

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
        Implement the sttyciarRunning() slot in SttyciarUI
        */
        void sttyciarRunning();

        /*!
        Implement the sttyciarStopped() slot in SttyciarUI
        */
        void sttyciarStopped();

        /*!
        Implement the updateStatistics() slot in SttyciarUI
        */
        void updateStatistics( shared_ptr<Statistics>& stats );

        /*!
        Implement the receiveDevices() slot in SttyciarUI
        */
        void receiveDevices( const QList<shared_ptr<Device> >& devices );

        /*!
        Implement the receiveActivatedDevices() slot in
        SttyciarUI
        */
        void receiveActivatedDevices(
            const QList<shared_ptr<Device> >& devices );

    protected slots:
        /*!
        Implement the exit() slot in SttyciarUI
        */
        void exit();

        /*!
        Slot to be initiated by the main user interface to start Sttyciar.

        This emits the startSttyciar signal specified in the interface.
        */
        void startSttyciarSlot(QString deviceType, shared_ptr<QStringList> devices, QString dumpFile);

        /*!
        Slot to be initiated by the main user interface to stop Sttyciar.

        This emits the stopSttyciar signal specified in the interface.
        */
        void stopSttyciarSlot();

        void restartSttyciarSlot(const QString& deviceType,
            const shared_ptr<QStringList>& deviceList,
            const QString& dumpFile);

    private:
        //! Pointer to the SttyciarGUIMain object that displays the main form.
        scoped_ptr<SttyciarGUIMain> _mainUI;

        //! Pointer to the SttyciarGUIStatistics object that displays the statistics form.
        scoped_ptr<SttyciarGUIStatistics> _statisticsUI;

        //! Available network devices to be implemented.
        QMap<int, QString> _availableNetworkDevices;

        //! Device Type being emulated
        QString _deviceType;

        //! File to dump packets to
        QString _dumpFile;

        //! List of devices being emulated
        shared_ptr<QStringList> _deviceList;
};

#endif
