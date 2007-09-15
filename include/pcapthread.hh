#ifndef __PCAPTHREAD_HH__
#define __PCAPTHREAD_HH__

#include <QtCore>
#include <boost/shared_ptr.hpp>
#include "pcap.h"
#include "device.hh"
#include "exceptions.hh"


using boost::shared_ptr;
class ALNetworkListener;

class PcapThread : public QThread
{
    Q_OBJECT

    public:
        PcapThread(const shared_ptr<Device>& device,int packetCaptureSize,
                    int timeout,shared_ptr<ALNetworkListener> alNetworkListener) throw(CannotOpenDeviceException);
        ~PcapThread();
        void stopListening();

    protected:
        void run() throw(CannotOpenDeviceException);
    private:
        shared_ptr<Device> _device;
        //shared_ptr<pcap_t> _source;
        int _pcapPacketCaptureSize;
        int _pcapTimeout;
        char _pcapErrorBuffer[PCAP_ERRBUF_SIZE];
        bool _listening;
        shared_ptr<ALNetworkListener> _alNetworkListener;
};

#endif // PCAPTHREAD_HH
