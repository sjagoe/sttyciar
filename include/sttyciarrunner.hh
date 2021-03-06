#ifndef __STTYCIARRUNNER_H__
#define __STTYCIARRUNNER_H__

#include <QtCore>
#include <QTimer>

#include <pcap.h>

#include <boost/shared_ptr.hpp>
#include <boost/scoped_ptr.hpp>

#include "sttyciarui_cli.hh"

using boost::shared_ptr;
using boost::scoped_ptr;

class AbstractionLayer;
class StatisticsLayer;
class PacketDumper;
class NetworkLogicLayer;

/*!
Main class that creates all objects, initialises them, connects them together,
and passes messages between them to provide the functionality of the system.
This class is simply instantiated in the main() function to start the
application (alongside a QApplication, of course).

\author Simon Jagoe
*/
class SttyciarRunner: public QObject
{
    Q_OBJECT
    public:
        /*!
        Constructor to create the user interface and abstraction layer, and
        perform initialisation tasks.
        */
        SttyciarRunner();

    private:
        //! Default time to update the NLL
        static const int NLL_UPDATE_TIMEOUT_MSEC = 30000;

        //! Default time to update statistics
        static const int STAT_UPDATE_TIMEOUT_MSEC = 1000;

        //! Maximum size of packets that can be captured
        static const int PACKET_CAPTURE_SIZE = 65535;

        //! Timeout of the pcap_next_ex method
        static const int PCAP_READ_TIMEOUT = 50;

        //! Identifier for a Hub device
        static const short HUB_TYPE = 1;

        //! Identifier for a Switch device
        static const short SWITCH_TYPE = 2;

        //! Link Type used to open the packet dump (Ethernet)
        static const int PDUMP_LINKTYPE = DLT_EN10MB;

        //! The PacketDumper object that will dump raw packet data in the pcap file format
        shared_ptr<PacketDumper> _packetDumper;

        //! Map of network system devices that can be created
        QMap<int, QString> _availableDevices;

        //! QTimer to call the update slot of the NetworkLogicLayer
        shared_ptr<QTimer> _nllUpdateTimer;

        //! QTimer to tell the StatisticsLayer to update the statitics
        shared_ptr<QTimer> _statisticsUpdateTimer;

        //! The User Interface object
        scoped_ptr<SttyciarUI> _ui;

        //! The AbstractionLayer object
        shared_ptr<AbstractionLayer> _abstractionLayer;

        //! The NetworkLogicLayer object
        shared_ptr<NetworkLogicLayer> _networkLogicLayer;

        //! The SL Object
        shared_ptr<StatisticsLayer> _statisticsLayer;

        //! Store the status if the application
        bool _sttyciarRunning;


    private slots:
        /*!
        Slot signalled by the UI to start Sttyciar with a set of Devices,
        and to act like a particular network system.

        \param deviceType The network System to emulate.
        \param devices The Devices to bind to the system.
        */
        void startSttyciar(QString deviceType, shared_ptr<QStringList> devices,
            QString dumpFile);

        /*!
        Slot signalled by the UI to stop Sttyciar and clean up back to the
        initial state.
        */
        void stopSttyciar();

        /*!
        Slot signalled by the UI to stop Sttyciar and exit.
        */
        void exitSttyciar();

        /*!
        Slot signalled by the NLLUpdateTimer so that the SttyciarRunner can
        signal the NLL to update with the number of milliseconds since the last
        update.
        */
        void nllUpdateTimeout();

        /*!
        Slot signalled by the StatisticsUpdateTimer so that the SttyciarRunner
        can signal the SL to update with the number of milliseconds since the
        last update.
        */
        void statisticsUpdateTimeout();

        /*!
        Slot signalled by the UI to restart the device as a bew type

        \param deviceType the type of device to emulate
        \param devices List of device names being used
        \param dumpFile The file to dump packets to
        */
        void restartSttyciar( const QString& deviceType,
            const shared_ptr<QStringList>& devices, const QString& dumpFile );

    signals:
        //! Signal to tell the QApplication to exit.
        void exit();

        /*!
        Signal the NLL to update.

        \param milliseconds The time since the last update in milliseconds.
        */
        void updateNLL( int milliseconds );

        /*!
        Signal the SL to update.

        \param milliseconds The time since the last update in milliseconds.
        */
        void updateStatistics( int milliseconds );
};

#endif
