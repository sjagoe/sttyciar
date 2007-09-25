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

void Device::startListening(int packetCaptureSize,int timeout) throw (CannotOpenDeviceException)
{
    #if defined(WIN32)
    if((this->_pcapDevice = pcap_open(this->getName().c_str(),packetCaptureSize,
							 PCAP_OPENFLAG_PROMISCUOUS | PCAP_OPENFLAG_NOCAPTURE_LOCAL | PCAP_OPENFLAG_MAX_RESPONSIVENESS,
							 timeout, NULL,this->_pcapErrorBuffer)) == NULL)
    #else
    if ((this->_pcapDevice = pcap_open_live(this->getName().c_str(),packetCaptureSize,true,timeout,this->_pcapErrorBuffer))==NULL)
    #endif
        throw CannotOpenDeviceException(this->_pcapErrorBuffer);


    this->_pcapSendThread.setDevice(this->_pcapDevice);
    this->_pcapSendThread.start();
}

void Device::stopListening()
{
    this->_pcapSendThread.stopRunning();
    pcap_close(this->_pcapDevice);
}

void Device::sendPacket(const shared_ptr<RawPacket>& packet)
{
    this->_pcapSendThread.addPacket(packet);
}

bool Device::operator==(Device& device) const
{
    return this->getName()==device.getName();
}

pcap_t* Device::getPcapDevice()
{
    return this->_pcapDevice;
}
