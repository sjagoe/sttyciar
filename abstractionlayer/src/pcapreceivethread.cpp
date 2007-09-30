//#include <iostream>
#include "pcapreceivethread.hh"
#include "alnetworklistener.hh"
#include "rawpacket.hh"
#include "interfaceroute.hh"

#include "pcapthreadticket.hh"

PcapReceiveThread::PcapReceiveThread()
{
}

PcapReceiveThread::PcapReceiveThread( const shared_ptr<Device>& device,weak_ptr<ALNetworkListener> alNetworkListener)
{
    this->_device=device;
    this->_alNetworkListener = alNetworkListener;
    this->_receiveBuffer.reset(new PcapThreadTicket( this->_alNetworkListener ));
}

PcapReceiveThread::~PcapReceiveThread()
{
}

void PcapReceiveThread::setDevice(weak_ptr<Device>& device)
{
    this->_device = device;
}

void PcapReceiveThread::setALNetworkListener(weak_ptr<ALNetworkListener>& alNetworkListener)
{
    this->_alNetworkListener = alNetworkListener;
    this->_receiveBuffer.reset(new PcapThreadTicket( this->_alNetworkListener ));
}

void PcapReceiveThread::stopListening()
{

    this->_listening=false;
    this->wait();
}

void PcapReceiveThread::run() throw(CannotOpenDeviceException)

{
    shared_ptr<Device> tempDevice = this->_device.lock();
    pcap_t* source = 0;
    source=tempDevice->getPcapSource();
    this->_listening = true;

    struct pcap_pkthdr *pkt_header;
    const u_char *pkt_data;
    int result=0;
    bool noterror=true;
    QList<DeviceAddress>  addresslist = (*(tempDevice)).getAddresses();
    std::string ipaddress = addresslist.front().getAddress().toIPString();
    shared_ptr<InterfaceRoute> interfaceRoute;

    while (this->_listening && noterror)
    {
        while (this->_listening && (result=pcap_next_ex(source,&pkt_header,&pkt_data) == 1))
        {
            shared_ptr<RawPacket> rawPacket(new RawPacket(pkt_header,pkt_data, tempDevice));
            this->_receiveBuffer->enqueue( rawPacket );

        }
        if (result<0)
        {
            noterror=false;
        }
    }
}
