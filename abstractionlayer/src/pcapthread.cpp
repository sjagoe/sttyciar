#include <iostream>
#include "pcapthread.hh"
#include "alnetworklistener.hh"
#include "rawpacket.hh"
#include "interfaceroute.hh"

#include "pcapthreadticket.hh"

PcapThread::PcapThread(const shared_ptr<Device>& device,int packetCaptureSize,
                        int timeout,weak_ptr<ALNetworkListener> alNetworkListener) throw (CannotOpenDeviceException) : _listening(false)
{
    this->_device=device;
    this->_pcapPacketCaptureSize=packetCaptureSize;
    this->_pcapTimeout=timeout;
    this->_alNetworkListener = alNetworkListener;

    //this->_receiveBuffer.reset(new LockableQueue<QPair<shared_ptr<RawPacket>,shared_ptr<InterfaceRoute> > >());
    this->_receiveBuffer.reset(
        new PcapThreadTicket( this->_alNetworkListener ) );
    //this->_alNetworkListener.lock()->registerLockableQueue(this->_receiveBuffer);
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
    shared_ptr<InterfaceRoute> interfaceRoute;
    //int count = 0;
    while (this->_listening && noterror)
    {
        while (this->_listening && (result=pcap_next_ex(source,&pkt_header,&pkt_data) == 1))
        {
            shared_ptr<RawPacket> rawPacket(new RawPacket(pkt_header,pkt_data));
            this->_receiveBuffer->enqueue( rawPacket, this->_device );
            /* // the 3 lines below are replaced with the single line above, the PcapThreadTicket object
            interfaceRoute.reset(new InterfaceRoute(this->_device));
            this->_receiveBuffer->push(qMakePair(rawPacket,interfaceRoute));
<<<<<<< TREE
            this->_alNetworkListener.lock()->packetReceived();*/
=======
            this->_alNetworkListener.lock()->packetReceived();
>>>>>>> MERGE-SOURCE
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
