#ifndef __PCAPRECEIVETHREAD_HH__
#define __PCAPRECEIVETHREAD_HH__

#include <QtCore>
//#include <iostream>
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

class PcapReceiveThread : public QThread
{
    Q_OBJECT

    public:
        PcapReceiveThread( const shared_ptr<Device>& device,
                    weak_ptr<ALNetworkListener> alNetworkListener) throw(CannotOpenDeviceException);
        ~PcapReceiveThread();
        void stopListening();
        int thread_number;

    protected:
        void run() throw(CannotOpenDeviceException);
    private:
        shared_ptr<Device> _device;
        int _pcapPacketCaptureSize;
        int _pcapTimeout;
        char _pcapErrorBuffer[PCAP_ERRBUF_SIZE];
        bool _listening;
        weak_ptr<ALNetworkListener> _alNetworkListener;
        scoped_ptr<PcapThreadTicket> _receiveBuffer;
        static int thread_counter;
};

#endif // __PCAPRECEIVETHREAD_HH__
