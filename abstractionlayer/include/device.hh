#ifndef DEVICE_H
#define DEVICE_H

#include <string>
#include <list>
#include "deviceaddress.hh"
#include "pcap.h"

using namespace std;

class Device
{
    public:
        Device();
        Device(pcap_if* pcapDevice);
        void setContents(pcap_if* pcapDevice);
        string getName() const;
        string getDescription() const;
        const list<DeviceAddress>& getAddresses() const;
        bool isLoopback() const;

    private:
        string _name;
        string _description;
        list<DeviceAddress> _addresses;
        unsigned int _flags;
        void createAddressList(pcap_if* pcapDevice);
};

#endif // DEVICE_H
