#ifndef DEVICE_H
#define DEVICE_H

#include <string>
#include <QList>
#include <boost/shared_ptr.hpp>
#include <pcap.h>
#include "deviceaddress.hh"
#include "lockablequeue.hh"
#include "rawpacket.hh"
#include "pcapreceivethread.hh"
#include "pcapsendthread.hh"
#include "exceptions.hh"
#include "alnetworklistener.hh"

using namespace std;
using boost::shared_ptr;
using boost::weak_ptr;

class Device
{
    public:
        Device();
        Device(const Device& device);
        Device(pcap_if* pcapDevice);
        void setSelf(weak_ptr<Device>& self);
        void setContents(pcap_if* pcapDevice);
        string getName() const;
        string getDescription() const;
        const QList<DeviceAddress>& getAddresses() const;
        bool isLoopback() const;
        bool operator==(Device& device) const;
        void startListening(int packetCaptureSize,int timeout,weak_ptr<ALNetworkListener>& alNetworkListener) throw (CannotOpenDeviceException);
        void stopListening();
        void sendPacket(const shared_ptr<RawPacket>& packet);
        pcap_t* getPcapSource();

    private:
        string _name;
        string _description;
        QList<DeviceAddress> _addresses;
        shared_ptr<PcapSendThread> _pcapSendThread;
        shared_ptr<PcapReceiveThread> _pcapReceiveThread;
        unsigned int _flags;
        pcap_t* _pcapSource;
        weak_ptr<Device> _self;
        char _pcapErrorBuffer[PCAP_ERRBUF_SIZE];
        void createAddressList(pcap_if* pcapDevice);
};

#endif // DEVICE_H
