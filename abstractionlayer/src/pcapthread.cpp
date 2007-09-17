#include "pcapthread.hh"
#include "alnetworklistener.hh"
#include "rawpacket.hh"
#include <iostream>

PcapThread::PcapThread(const shared_ptr<Device>& device,int packetCaptureSize,
                        int timeout,weak_ptr<ALNetworkListener> alNetworkListener) throw (CannotOpenDeviceException) : _listening(false)
{
    this->_device=device;
    this->_pcapPacketCaptureSize=packetCaptureSize;
    this->_pcapTimeout=timeout;
    this->_alNetworkListener = alNetworkListener;
}

PcapThread::~PcapThread()
{
}

void PcapThread::stopListening()
{

    this->_listening=false;
}

void PcapThread::run() throw(CannotOpenDeviceException)

{
    pcap_t* source=NULL;
    this->_listening = true;

    if ((source=pcap_open_live(this->_device->getName().c_str(),this->_pcapPacketCaptureSize,
                            true,this->_pcapTimeout,this->_pcapErrorBuffer))==NULL)
        this->_listening = false;


    struct pcap_pkthdr *pkt_header;
    const u_char *pkt_data;
    int result=0;
    bool noterror=true;
    list<DeviceAddress>  addresslist = (*(this->_device)).getAddresses();
    std::string ipaddress = addresslist.front().getAddress().toIPString();
    //int count = 0;
    while (this->_listening && noterror)
    {
        while (this->_listening && (result=pcap_next_ex(source,&pkt_header,&pkt_data) == 1))
        {
            shared_ptr<RawPacket> rawPacket(new RawPacket(pkt_header,pkt_data));
            this->_alNetworkListener.lock()->packetReceived(rawPacket,this->_device);
            //std::cout << count++ << ": " << ipaddress << std::endl;
        }
        if (result<0)
        {
            noterror=false;
        }
    }

    pcap_close(source);
    delete pkt_header;
    delete pkt_data;





}

//void PcapThread::openAda
