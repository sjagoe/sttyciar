#ifndef __PCAPTHREAD_HH__
#define __PCAPTHREAD_HH__

#include <QtCore>
#include <boost/shared_ptr.hpp>
#include "pcap.h"
#include "device.hh"
#include "exceptions.hh"

using boost::shared_ptr;

class PcapThread : public QThread
{
    Q_OBJECT

    public:
        PcapThread(const shared_ptr<Device>& device,int packetCaptureSize,int timeout) throw(CannotOpenDeviceException);
        ~PcapThread();

    protected:
        void run() throw(CannotOpenDeviceException);
    private:
        shared_ptr<Device> _device;
        //shared_ptr<pcap_t> _source;
        int _pcapPacketCaptureSize;
        int _pcapTimeout;
        char _pcapErrorBuffer[PCAP_ERRBUF_SIZE];
        bool _running;
};

#endif // PCAPTHREAD_HH
