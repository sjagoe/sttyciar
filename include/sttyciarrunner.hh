#ifndef __STTYCIARRUNNER_H__
#define __STTYCIARRUNNER_H__

#include <QtCore>

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
        static const int PACKET_CAPTURE_SIZE = 65535;
        static const int PCAP_READ_TIMEOUT = 100;

        scoped_ptr<SttyciarUI> _ui;
        shared_ptr<AbstractionLayer> _abstractionLayer;
        shared_ptr<NetworkLogicLayer> _networkLogicLayer;

    private slots:
        void startSttyciar(short deviceType);
        void stopSttyciar();
        void exitSttyciar();

    signals:
        void exit();
};

#endif
