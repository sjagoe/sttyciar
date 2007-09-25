//#include <iostream>
#include "pcapsendthread.hh"
#include "rawpacket.hh"

#include "ethernetiiframe.hh"
#include "ipv4datagram.hh"

int PcapSendThread::thread_counter = 1;

PcapSendThread::PcapSendThread()
{
    this->_running = false;
    this->thread_number = thread_counter++;
}

PcapSendThread::PcapSendThread(pcap_t* pcapDevice)
{
    this->_running = false;
    this->_pcapDevice = pcapDevice;
    this->thread_number = thread_counter++;
}

PcapSendThread::~PcapSendThread()
{
}

void PcapSendThread::setDevice(pcap_t* pcapDevice)
{
    this->_pcapDevice = pcapDevice;
}

void PcapSendThread::addPacket(const shared_ptr<RawPacket>& packet)
{
//    std::cout << "PcapSendThread:addPacket()" << std::endl;
    this->_packetQueue.push(packet);
//    this->_mutex.lock();
//    this->_mutex.unlock();
    this->_waitCondition.wakeAll();
//    std::cout << "End PcapSendThread:addPacket()" << std::endl;
}

void PcapSendThread::stopRunning()
{
    this->_running = false;
//    this->_mutex.lock();
//    this->_mutex.unlock();
    this->_waitCondition.wakeAll();
}

void PcapSendThread::run()
{
    //std::cout << "\nsend: start - thread number: " << thread_number << std::endl;
    this->_running = true;

    shared_ptr<RawPacket> rawPacket;
    while (this->_running)
    {
        if (!this->_packetQueue.isEmpty())
        {
            _packetQueue.pop(rawPacket);
//            std::cout << "Packet about to be sent" << std::endl;

//            shared_ptr<EthernetIIFrame> frame( new EthernetIIFrame( rawPacket ) );
//            mac_t dm = frame->getDestinationMAC();
//            mac_t sm = frame->getSourceMAC();
//            ethertype_t tt = frame->getEtherType();
//
//            printf( "\nSending Destination MAC: %02X:%02X:%02X:%02X:%02X:%02X\n", dm.b1, dm.b2, dm.b3, dm.b4, dm.b5, dm.b6 );
//
//            printf( "Sending     Source MAC: %02X:%02X:%02X:%02X:%02X:%02X\n", sm.b1, sm.b2, sm.b3, sm.b4, sm.b5, sm.b6 );

            pcap_sendpacket(this->_pcapDevice,rawPacket->getPacketPointer(),rawPacket->getPacketLength());
        }
        else
        {
            this->_mutex.lock();
            this->_waitCondition.wait(&this->_mutex);
            this->_mutex.unlock();
        }

    }
//    std::cout << "\nsend: finish - thread number: " << thread_number << std::endl;
    //pcap_close(source);
}
