#ifndef __STTYCIARRUNNER_H__
#define __STTYCIARRUNNER_H__

#include <QtCore>
#include <QTimer>

#include <boost/shared_ptr.hpp>
#include <boost/scoped_ptr.hpp>

#include "sttyciarui_cli.hh"

using boost::shared_ptr;
using boost::scoped_ptr;

class AbstractionLayer;
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
        static const int NLL_UPDATE_TIMEOUT_MSEC = 30000; //! Default time to update the NLL
        static const int STAT_UPDATE_TIMEOUT_MSEC = 5000; //! Default time to update statistics

        static const int PACKET_CAPTURE_SIZE = 65535; //! Maximum size of packets that can be captured
        static const int PCAP_READ_TIMEOUT = 50; //! Timeout of the pcap_next_ex method
        static const short HUB_TYPE = 1; //! Identifier for a Hub device
        static const short SWITCH_TYPE = 2; //! Identifier for a Switch device
        QMap<int, QString> _availableDevices; //! Map of network system devices that can be created

        shared_ptr<QTimer> _nllUpdateTimer; //! QTimer to call the update slot of the NetworkLogicLayer
        shared_ptr<QTimer> _statisticsUpdateTimer; //! QTimer to tell the StatisticsLayer to update the statitics

        scoped_ptr<SttyciarUI> _ui; //! The User Interface object
        shared_ptr<AbstractionLayer> _abstractionLayer; //! The AbstractionLayer object
        shared_ptr<NetworkLogicLayer> _networkLogicLayer; //! The NetworkLogicLayer object

    private slots:
        /*!
        Slot signalled by the UI to start Sttyciar with a set of Devices,
        and to act like a particular network system.

        \param deviceType The network System to emulate.
        \param devices The Devices to bind to the system.
        */
        void startSttyciar(QString deviceType, shared_ptr<QStringList> devices);

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
        void statisticsUpdateTimeout();

        /*!
        Slot signalled by the StatisticsUpdateTimer so that the SttyciarRunner
        can signal the SL to update with the number of milliseconds since the
        last update.
        */

    signals:
        //! Signal to tell the QApplication to exit.
        void exit();

        /*!
        Signal the NLL to update.

        \param milliseconds The time since the last update in milliseconds.
        */
        void updateNLL( int milliseconds );
        void updateStatistics( int milliseconds );

        /*!
        Signal the SL to update.

        \param milliseconds The time since the last update in milliseconds.
        */
};

#endif
