#ifndef __PCAPRECEIVETHREAD_HH__
#define __PCAPRECEIVETHREAD_HH__

#include <QtCore>
//#include <iostream>
#include <boost/shared_ptr.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include "pcap.h"
//#include "device.hh"
#include "exceptions.hh"
#include "lockablequeue.hh"


using boost::shared_ptr;
using boost::scoped_ptr;
using boost::weak_ptr;
class ALNetworkListener;
class RawPacket;
class InterfaceRoute;
class Device;

class PcapThreadTicket;

class PcapReceiveThread : public QThread
{
    Q_OBJECT

    public:
        PcapReceiveThread();
        PcapReceiveThread( const shared_ptr<Device>& device,
                    weak_ptr<ALNetworkListener> alNetworkListener) throw(CannotOpenDeviceException);
        ~PcapReceiveThread();
        void setDevice(weak_ptr<Device>& device);
        void setALNetworkListener(weak_ptr<ALNetworkListener>& alNetworkListener);
        void stopListening();

    protected:
        void run() throw(CannotOpenDeviceException);
    private:
        weak_ptr<Device> _device;
        int _pcapPacketCaptureSize;
        int _pcapTimeout;
        char _pcapErrorBuffer[PCAP_ERRBUF_SIZE];
        bool _listening;
        weak_ptr<ALNetworkListener> _alNetworkListener;
        scoped_ptr<PcapThreadTicket> _receiveBuffer;
};

#endif // __PCAPRECEIVETHREAD_HH__