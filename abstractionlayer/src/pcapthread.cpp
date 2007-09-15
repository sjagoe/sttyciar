#include "pcapthread.hh"

PcapThread::PcapThread(const shared_ptr<Device>& device,int packetCaptureSize,int timeout) throw (CannotOpenDeviceException)
{
    this->_device=device;
    this->_pcapPacketCaptureSize=packetCaptureSize;
    this->_pcapTimeout=timeout;
}

PcapThread::~PcapThread()
{
}

void PcapThread::run() throw(CannotOpenDeviceException)

{
    pcap_t* source;

    if ((source=pcap_open(this->_device->getName().c_str(),this->_pcapPacketCaptureSize,
                            PCAP_OPENFLAG_PROMISCUOUS,this->_pcapTimeout,
                            NULL,this->_pcapErrorBuffer))==NULL)
        throw CannotOpenDeviceException(this->_pcapErrorBuffer);

    struct pcap_pkthdr *pkt_header;
    const u_char *pkt_data;
    this->_running = true;
    int result;
    while (this->_running && (result=pcap_next_ex(source,&pkt_header,&pkt_data) >= 0))
    {

    }
}

//void PcapThread::openAda
