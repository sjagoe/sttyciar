#include "pcapsendthread.hh"
#include "rawpacket.hh"

PcapSendThread::PcapSendThread()
{
    this->_running = false;
}

PcapSendThread::PcapSendThread(pcap_t* device)
{
    this->_running = false;
    this->_device = device;
}

PcapSendThread::~PcapSendThread()
{
}

void PcapSendThread::setDevice(pcap_t* device)
{
    this->_device = device;
}

void PcapSendThread::addPacket(const shared_ptr<RawPacket>& packet)
{
    this->_packetQueue.push(packet);
    this->_mutex.lock();
    this->_mutex.unlock();
    this->_waitCondition.wakeAll();
}

void PcapSendThread::stopRunning()
{
    this->_running = false;
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
            pcap_sendpacket(this->_device,rawPacket->getPacketPointer(),rawPacket->getPacketLength());
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
