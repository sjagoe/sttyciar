#ifndef __PCAPSENDTHREAD_HH__
#define __PCAPSENDTHREAD_HH__

#include <string>
#include <QtCore>
#include <boost/shared_ptr.hpp>
#include "pcap.h"
#include "lockablequeue.hh"

using boost::shared_ptr;
using std::string;

class RawPacket;

class PcapSendThread : public QThread
{
    Q_OBJECT

    public:
        PcapSendThread();
        PcapSendThread(const string& deviceName);
        ~PcapSendThread();
        void setDeviceName(const string& deviceName);
        void addPacket(const shared_ptr<RawPacket>& packet);
        void stopRunning();
    protected:
        void run();

    private:
        LockableQueue<shared_ptr<RawPacket> > _packetQueue;
        bool _running;
        QWaitCondition _waitCondition;
        QMutex _mutex;
        string _deviceName;
        char _pcapErrorBuffer[PCAP_ERRBUF_SIZE];

};

#endif // __PCAPSENDTHREAD_HH__
