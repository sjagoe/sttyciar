//#include <iostream>
#include "pcapreceivethread.hh"
#include "alnetworklistener.hh"
#include "rawpacket.hh"
#include "interfaceroute.hh"

#include "pcapthreadticket.hh"

int PcapReceiveThread::thread_counter = 1;

PcapReceiveThread::PcapReceiveThread( const shared_ptr<Device>& device,
                        weak_ptr<ALNetworkListener> alNetworkListener) throw (CannotOpenDeviceException) : _listening(false)
{
    this->_device=device;
    this->_alNetworkListener = alNetworkListener;

    this->_receiveBuffer.reset(new PcapThreadTicket( this->_alNetworkListener ));
    this->thread_number = thread_counter++;
}

PcapReceiveThread::~PcapReceiveThread()
{
}

void PcapReceiveThread::stopListening()
{

    this->_listening=false;
}

void PcapReceiveThread::run() throw(CannotOpenDeviceException)

{
    //std::cout << "\nreceive: start - thread number: " << thread_number << std::endl;
    pcap_t* source = 0;
    source=this->_device->getPcapDevice();
    this->_listening = true;

    struct pcap_pkthdr *pkt_header;
    const u_char *pkt_data;
    int result=0;
    bool noterror=true;
    QList<DeviceAddress>  addresslist = (*(this->_device)).getAddresses();
    std::string ipaddress = addresslist.front().getAddress().toIPString();
    shared_ptr<InterfaceRoute> interfaceRoute;
    //int count = 0;
    while (this->_listening && noterror)
    {
        while (this->_listening && (result=pcap_next_ex(source,&pkt_header,&pkt_data) == 1))
        {
            shared_ptr<RawPacket> rawPacket(new RawPacket(pkt_header,pkt_data, this->_device));
//            if (rawPacket.get() == 0)
//                std::cout << "Null Pointer in PcapReceiveThread::run() - 1" << std::endl;
//            else
//                std::cout << "Non-Null Pointer in PcapReceiveThread::run() - 1" << std::endl;
            this->_receiveBuffer->enqueue( rawPacket );
//            if (rawPacket.get() == 0)
//                std::cout << "Null Pointer in PcapReceiveThread::run() - 2" << std::endl;
//            else
//                std::cout << "Non-Null Pointer in PcapReceiveThread::run() - 2" << std::endl;
            //std::cout << count++ << ": " << ipaddress << std::endl;
        }
        if (result<0)
        {
            noterror=false;
        }
    }
//    std::cout << "\nreceive: finish - thread number: " << thread_number << std::endl;
//    delete pkt_header;
//    delete pkt_data;


}
