#include "device.hh"
#include <ext/algorithm>
//#include <iostream>
#include <sstream>

Device::Device()
{
    this->_pcapSource = NULL;
    this->_pcapSendThread.reset(new PcapSendThread());
    this->_pcapReceiveThread.reset(new PcapReceiveThread());
}

/*customized copy constructor to esnure that the error buffer is a copy and not just a pointer to the same error buffer*/
Device::Device(const Device& device)
{
    this->_pcapSource = NULL;
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
    this->_pcapSource = NULL;
    this->setContents(pcapDevice);
    this->_pcapSendThread.reset(new PcapSendThread());
    this->_pcapReceiveThread.reset(new PcapReceiveThread());
}

void Device::setSelf(weak_ptr<Device>& self)
{
    _self = self;
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

bool Device::isSupported()
{
    pcap_t* testSource;
    #if defined(WIN32)
    if((testSource=pcap_open(this->getName().c_str(),65535,
				 PCAP_OPENFLAG_PROMISCUOUS | PCAP_OPENFLAG_NOCAPTURE_LOCAL | PCAP_OPENFLAG_MAX_RESPONSIVENESS,
                 10, NULL,this->_pcapErrorBuffer)) == NULL)
    #else
    if ((testSource=pcap_open_live(this->getName().c_str(),65535,true,10,this->_pcapErrorBuffer))==NULL)
    #endif
        return false;

    bool supported = false;
    int* dlTypes;
    int amtDlTypes = pcap_list_datalinks(testSource,&dlTypes);

    for (int i = 0; i < amtDlTypes; i++)
    {
        if (dlTypes[i] == DLT_EN10MB)
        {
            supported = true;
            break;
        }
    }
    if ( (amtDlTypes > 0) && (dlTypes != NULL) )
        free(dlTypes);

    pcap_close(testSource);

    return supported;
}

void Device::open(int packetCaptureSize,int timeout,weak_ptr<ALNetworkListener>& alNetworkListener,bool filterEnabled) throw (CannotOpenDeviceException)
{
    #if defined(WIN32)
    if((this->_pcapSource = pcap_open(this->getName().c_str(),packetCaptureSize,
							 PCAP_OPENFLAG_PROMISCUOUS | PCAP_OPENFLAG_NOCAPTURE_LOCAL | PCAP_OPENFLAG_MAX_RESPONSIVENESS,
							 timeout, NULL,this->_pcapErrorBuffer)) == NULL)
    #else
    if ((this->_pcapSource = pcap_open_live(this->getName().c_str(),packetCaptureSize,true,timeout,this->_pcapErrorBuffer))==NULL)
    #endif
        throw CannotOpenDeviceException(this->_pcapErrorBuffer);

    if (filterEnabled)
        try
        {
            this->setFilter();
        }
        catch (PcapFilterException pfe)
        {
            //std::cout << "error setting the filter\n";
        }

    this->_pcapSendThread->setSource(this->_pcapSource);

    this->_pcapReceiveThread->setDevice(this->_self);
    this->_pcapReceiveThread->setALNetworkListener(alNetworkListener);
}

void Device::close()
{
    if (this->_pcapSource != NULL)
    {
        pcap_close(this->_pcapSource);
        this->_pcapSource = NULL;
    }
}

void Device::startListening() throw (CannotStartListeningException)
{
    if ( this->_pcapSource != NULL )
    {
        this->_pcapSendThread->start();
        this->_pcapReceiveThread->start();
    }
    else
        throw CannotStartListeningException("Cannot start listening: Device not started");
}

void Device::stopListening()
{
    this->_pcapSendThread->stopRunning();
    this->_pcapReceiveThread->stopListening();
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

void Device::setFilter() throw (PcapFilterException)
{
    std::ostringstream filterStringStream;
    int count = 0;
    filterStringStream << "not ( ";
    for (QList<DeviceAddress>::const_iterator iter = this->_addresses.begin(); iter!=this->_addresses.end(); iter++)
    {
        if (count != 0)
            filterStringStream << "or ";
        filterStringStream << "dst host " << iter->getAddress().toIPString() << " ";
        count++;
    }
    filterStringStream << ")";
    struct bpf_program compiledFilter;

     //1 is added for null character
    char* filterString = new char[filterStringStream.str().length()+1];
    filterStringStream.str().copy(filterString,filterStringStream.str().length(),0);

    // string::copy doesn't put in the null character, which is needed, so put it in manually
    filterString[filterStringStream.str().length()] = '\0';

//    std::cout << filterString << std::endl;
    if (pcap_compile(this->_pcapSource,&compiledFilter,filterString,1,0)<0)
        throw PcapFilterException(pcap_geterr(this->_pcapSource));


    if(pcap_setfilter(this->_pcapSource,&compiledFilter)<0)
        throw PcapFilterException(pcap_geterr(this->_pcapSource));


    pcap_freecode(&compiledFilter);

}
