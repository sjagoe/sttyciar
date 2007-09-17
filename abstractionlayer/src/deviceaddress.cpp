#include <iostream>

#include "deviceaddress.hh"

using std::cout;
using std::endl;

const int DeviceAddress::DEFAULT_ADDRESS_LENGTH;

DeviceAddress::DeviceAddress()
{
}

DeviceAddress::DeviceAddress(pcap_addr* pcapAddress)
{
    this->setContents(pcapAddress);
}

void DeviceAddress::setContents(pcap_addr* pcapAddress)
{
    if (pcapAddress->addr != NULL)
        this->_addr.setContents(pcapAddress->addr);
    if (pcapAddress->netmask)
        this->_netmask.setContents(pcapAddress->netmask);
    if (pcapAddress->broadaddr)
        this->_broadAddr.setContents(pcapAddress->broadaddr);

 /*   DeviceAddress::copySockAddr(*(pcapAddress->addr),this->_addr);
    DeviceAddress::copySockAddr(*(pcapAddress->netmask),this->_netmask);
    DeviceAddress::copySockAddr(*(pcapAddress->broadaddr),this->_broadAddr);*/

    //this pointer may be null as pcap_findalldevs does not fill this value, where pcap_findalldevs_ex does
    if (pcapAddress->dstaddr != NULL)
        this->_dstAddr.setContents(pcapAddress->dstaddr);

}

const Address& DeviceAddress::getAddress() const
{
    return this->_addr;
}

const Address& DeviceAddress::getNetmask() const
{
    return this->_netmask;
}

const Address& DeviceAddress::getBroadcastAddress() const
{
    return this->_broadAddr;
}

const Address& DeviceAddress::getDestinationAddress() const
{
    return this->_dstAddr;
}

void DeviceAddress::copySockAddr(sockaddr &src, sockaddr &dst)
{
    dst.sa_family = src.sa_family;
    __gnu_cxx::copy_n(src.sa_data,DeviceAddress::DEFAULT_ADDRESS_LENGTH,dst.sa_data);
}
