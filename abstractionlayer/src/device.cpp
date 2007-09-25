#include "device.hh"
#include <ext/algorithm>
#include <iostream>

Device::Device()
{
    this->_pcapSendThread.reset(new PcapSendThread());
    this->_pcapReceiveThread.reset(new PcapReceiveThread());
}

/*customized copy constructor to esnure that the error buffer is a copy and not just a pointer to the same error buffer*/
Device::Device(const Device& device)
{
    this->_name = device._name;
    this->_description = device._description;
    this->_addresses = device._addresses;
    this->_flags = device._flags;
    this->_pcapSource = device._pcapSource;
    __gnu_cxx::copy_n(device._pcapErrorBuffer,PCAP_ERRBUF_SIZE,this->_pcapErrorBuffer);
    this->_pcapSendThread = device._pcapSendThread;
    this->_pcapReceiveThread = device._pcapReceiveThread;

}

Device::Device(pcap_if* pcapDevice)
{
    this->setContents(pcapDevice);
    this->_pcapSendThread.reset(new PcapSendThread());
    this->_pcapReceiveThread.reset(new PcapReceiveThread());
}

void Device::setContents(pcap_if* pcapDevice)
{
    this->_name=pcapDevice->name;
    if (pcapDevice->description != NULL)
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

const QList<DeviceAddress>& Device::getAddresses() const
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

void Device::startListening(int packetCaptureSize,int timeout,weak_ptr<ALNetworkListener>& alNetworkListener) throw (CannotOpenDeviceException)
{
    #if defined(WIN32)
    if((this->_pcapSource = pcap_open(this->getName().c_str(),packetCaptureSize,
							 PCAP_OPENFLAG_PROMISCUOUS | PCAP_OPENFLAG_NOCAPTURE_LOCAL | PCAP_OPENFLAG_MAX_RESPONSIVENESS,
							 timeout, NULL,this->_pcapErrorBuffer)) == NULL)
    #else
    if ((this->_pcapSource = pcap_open_live(this->getName().c_str(),packetCaptureSize,true,timeout,this->_pcapErrorBuffer))==NULL)
    #endif
        throw CannotOpenDeviceException(this->_pcapErrorBuffer);


    this->_pcapSendThread->setSource(this->_pcapSource);

    shared_ptr<Device> tempDeviceCopy(new Device(*this));
    this->_pcapReceiveThread->setDevice(tempDeviceCopy);
    this->_pcapReceiveThread->setALNetworkListener(alNetworkListener);

    this->_pcapSendThread->start();
    this->_pcapReceiveThread->start();
}

void Device::stopListening()
{
    this->_pcapSendThread->stopRunning();
    this->_pcapReceiveThread->stopListening();
    pcap_close(this->_pcapSource);
}

void Device::sendPacket(const shared_ptr<RawPacket>& packet)
{
    this->_pcapSendThread->addPacket(packet);
}

bool Device::operator==(Device& device) const
{
    return this->getName()==device.getName();
}

pcap_t* Device::getPcapSource()
{
    return this->_pcapSource;
}
