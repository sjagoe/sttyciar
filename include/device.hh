#ifndef DEVICE_H
#define DEVICE_H

#include <string>
#include <QList>
#include <boost/shared_ptr.hpp>
#include <pcap.h>
#include "deviceaddress.hh"
#include "lockablequeue.hh"
#include "packet.hh"
#include "pcapsendthread.hh"

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
        void sendPacket(shared_ptr<Packet>& packet);

    private:
        string _name;
        string _description;
        QList<DeviceAddress> _addresses;
        PcapSendThread _pcapSendThread;
        unsigned int _flags;
        void createAddressList(pcap_if* pcapDevice);
};

#endif // DEVICE_H
