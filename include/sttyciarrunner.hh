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

class SttyciarRunner: public QObject
{
    Q_OBJECT
    public:
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
        void startSttyciar(QString deviceType, shared_ptr<QStringList> devices);
        void stopSttyciar();
        void exitSttyciar();

        void nllUpdateTimeout();
        void statisticsUpdateTimeout();

    signals:
        void exit();

        void updateNLL( int milliseconds );
        void updateStatistics( int milliseconds );
};

#endif
