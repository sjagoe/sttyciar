#ifndef __PCAPSENDTHREAD_HH__
#define __PCAPSENDTHREAD_HH__

#include <QtCore>
#include <boost/shared_ptr.hpp>

using boost::shared_ptr;

class Packet;

class PcapSendThread : public QThread
{
    Q_OBJECT

    public:
        PcapSendThread();
        ~PcapSendThread();
        void addPacket(shared_ptr<Packet>& packet);
    protected:
        void run();
};

#endif // __PCAPSENDTHREAD_HH__
