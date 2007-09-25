#ifndef DEVICE_H
#define DEVICE_H

#include <string>
#include <QList>
#include <boost/shared_ptr.hpp>
#include <pcap.h>
#include "deviceaddress.hh"
#include "lockablequeue.hh"
#include "rawpacket.hh"
#include "pcapsendthread.hh"
#include "exceptions.hh"

using namespace std;
using boost::shared_ptr;

class Device
{
    public:
        Device();
        Device(pcap_if* pcapDevice);
        void setContents(pcap_if* pcapDevice);
        string getName() const;
        string getDescription() const;
        const QList<DeviceAddress>& getAddresses() const;
        bool isLoopback() const;
        bool operator==(Device& device) const;
        void startListening(int packetCaptureSize,int timeout) throw (CannotOpenDeviceException);
        void stopListening();
        void sendPacket(const shared_ptr<RawPacket>& packet);
        pcap_t* getPcapSource();

    private:
        string _name;
        string _description;
        QList<DeviceAddress> _addresses;
        PcapSendThread _pcapSendThread;
        unsigned int _flags;
        void createAddressList(pcap_if* pcapDevice);
        pcap_t* _pcapSource;
        char _pcapErrorBuffer[PCAP_ERRBUF_SIZE];
};

#endif // DEVICE_H
