//#include <iostream>
#include "pcapsendthread.hh"
#include "rawpacket.hh"

#include "ethernetiiframe.hh"
#include "ipv4datagram.hh"

PcapSendThread::PcapSendThread()
{
    this->_running = false;
}

PcapSendThread::PcapSendThread(pcap_t* pcapSource)
{
    this->_running = false;
    this->_pcapSource = pcapSource;
}

PcapSendThread::~PcapSendThread()
{
}

void PcapSendThread::setSource(pcap_t* pcapSource)
{
    this->_pcapSource = pcapSource;
}

void PcapSendThread::addPacket(const shared_ptr<RawPacket>& packet)
{
    this->_packetQueue.push(packet);
//    this->_mutex.lock();
//    this->_mutex.unlock();
    this->_waitCondition.wakeAll();

}

void PcapSendThread::stopRunning()
{
    this->_running = false;
//    this->_mutex.lock();
//    this->_mutex.unlock();
    this->_waitCondition.wakeAll();
    this->wait();

}

void PcapSendThread::run()
{
    this->_running = true;

    shared_ptr<RawPacket> rawPacket;
    while (this->_running)
    {
        if (!this->_packetQueue.isEmpty())
        {
            _packetQueue.pop(rawPacket);
            pcap_sendpacket(this->_pcapSource,rawPacket->getPacketPointer(),rawPacket->getPacketLength());
        }
        else
        {
            this->_mutex.lock();
            this->_waitCondition.wait(&this->_mutex);
            this->_mutex.unlock();
        }

    }
    //pcap_close(source);
}
