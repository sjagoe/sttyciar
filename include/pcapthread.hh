#ifndef __PCAPTHREAD_HH__
#define __PCAPTHREAD_HH__

#include <QtCore>
#include <boost/shared_ptr.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include "pcap.h"
#include "device.hh"
#include "exceptions.hh"
#include "lockablequeue.hh"


using boost::shared_ptr;
using boost::scoped_ptr;
using boost::weak_ptr;
class ALNetworkListener;
class RawPacket;
class InterfaceRoute;

class PcapThreadTicket;

class PcapThread : public QThread
{
    Q_OBJECT

    public:
        PcapThread(const shared_ptr<Device>& device,int packetCaptureSize,
                    int timeout,weak_ptr<ALNetworkListener> alNetworkListener) throw(CannotOpenDeviceException);
        ~PcapThread();
        void stopListening();

    protected:
        void run() throw(CannotOpenDeviceException);
    private:
        shared_ptr<Device> _device;
        int _pcapPacketCaptureSize;
        int _pcapTimeout;
        char _pcapErrorBuffer[PCAP_ERRBUF_SIZE];
        bool _listening;
        weak_ptr<ALNetworkListener> _alNetworkListener;
        //shared_ptr<LockableQueue<QPair<shared_ptr<RawPacket>,shared_ptr<InterfaceRoute> > > > _receiveBuffer;
        scoped_ptr<PcapThreadTicket> _receiveBuffer;
};

#endif // PCAPTHREAD_HH
