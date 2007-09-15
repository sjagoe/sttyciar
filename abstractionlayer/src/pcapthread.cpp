#include "pcapthread.hh"
#include "alnetworklistener.hh"

PcapThread::PcapThread(const shared_ptr<Device>& device,int packetCaptureSize,
                        int timeout,shared_ptr<ALNetworkListener> alNetworkListener) throw (CannotOpenDeviceException)
{
    this->_device=device;
    this->_pcapPacketCaptureSize=packetCaptureSize;
    this->_pcapTimeout=timeout;
    this->_alNetworkListener = alNetworkListener;
}

PcapThread::~PcapThread()
{
}

void PcapThread::run() throw(CannotOpenDeviceException)

{
    pcap_t* source;
    this->_running = true;

    if ((source=pcap_open(this->_device->getName().c_str(),this->_pcapPacketCaptureSize,
                            PCAP_OPENFLAG_PROMISCUOUS,this->_pcapTimeout,
                            NULL,this->_pcapErrorBuffer))==NULL)
        this->_running = false;


    struct pcap_pkthdr *pkt_header;
    const u_char *pkt_data;
    int result=0;
    bool noterror=true;

    while (this->_running && noterror)
    {
        while (this->_running && (result=pcap_next_ex(source,&pkt_header,&pkt_data) == 1))
        {
            shared_ptr<RawPacket> rawPacket(new RawPacket(pkt_header,pkt_data));
            this->_alNetworkListener.packetReceived(rawPacket,this->_device);
        }
        if (result<0)
        {
            noterror=false;
        }
    }


    delete pkt_header;
    delete pkt_data;





}

//void PcapThread::openAda
