#ifndef __PCAPSENDTHREAD_HH__
#define __PCAPSENDTHREAD_HH__

#include <QtCore>
#include <boost/shared_ptr.hpp>
#include "lockablequeue.hh"

using boost::shared_ptr;

class RawPacket;

class PcapSendThread : public QThread
{
    Q_OBJECT

    public:
        PcapSendThread();
        ~PcapSendThread();
        void addPacket(const shared_ptr<RawPacket>& packet);
    protected:
        void run();

    private:
        LockableQueue<shared_ptr<RawPacket> > _packetQueue;
        bool _running;
};

#endif // __PCAPSENDTHREAD_HH__
