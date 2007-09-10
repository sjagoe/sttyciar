#ifndef ADDRESS_H_INCLUDED
#define ADDRESS_H_INCLUDED
#include <winsock.h>
#include <ext/algorithm>
#include "pcap.h"
#include "address.hh"


class DeviceAddress
{
    public:
        DeviceAddress();
        DeviceAddress(pcap_addr* pcapAddress);
        void setContents(pcap_addr* pcapAddress);
        const Address& getAddress() const;
        const Address& getNetmask() const;
        const Address& getBroadcastAddress() const;
        const Address& getDestinationAddress() const;

    private:
        Address _addr;
        Address _netmask;
        Address _broadAddr;
        Address _dstAddr;
        static void copySockAddr(sockaddr &src, sockaddr &dst);
        static const int DEFAULT_ADDRESS_LENGTH = 14;
};


#endif // ADDRESS_H_INCLUDED
