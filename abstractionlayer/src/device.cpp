#include "device.hh"

Device::Device()
{
}

Device::Device(pcap_if* pcapDevice)
{
    this->setContents(pcapDevice);
}

void Device::setContents(pcap_if* pcapDevice)
{
    this->_name=pcapDevice->name;
    this->_description=pcapDevice->description;
    this->createAddressList(pcapDevice);
    this->_flags=pcapDevice->flags;
}

string Device::getName() const
{
    return this->_name;
}

string Device::getDescription() const
{
    return this->_description;
}

const list<DeviceAddress>& Device::getAddresses() const
{
    return this->_addresses;
}

bool Device::isLoopback () const
{
    return this->_flags & PCAP_IF_LOOPBACK;
}

void Device::createAddressList(pcap_if* pcapDevice)
{
    DeviceAddress address;
    _addresses.clear();
    for(pcap_addr* pcapTempAddress = pcapDevice->addresses; pcapTempAddress != NULL; pcapTempAddress = pcapTempAddress->next)
    {
        address.setContents(pcapTempAddress);
        _addresses.push_back(address);
    }
}

bool Device::operator==(Device& device) const
{
    return this->getName()==device.getName();
}


