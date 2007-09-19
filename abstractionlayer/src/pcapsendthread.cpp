#include "pcapsendthread.hh"
#include "rawpacket.hh"
#include "pcap.h"

PcapSendThread::PcapSendThread()
{
    this->_running = false;
}

PcapSendThread::~PcapSendThread()
{
}

void PcapSendThread::addPacket(const shared_ptr<RawPacket>& packet)
{
    this->_packetQueue.push(packet);
    this->_waitCondition.wakeAll();
}

void PcapSendThread::run()
{
    this->_running = true;
    shared_ptr<RawPacket> rawPacket;
    while (this->_running)
    {
        if (!this->_packetQueue.isEmpty())
            _packetQueue.pop(rawPacket);
        else
        {
            this->mutex.lock();
            this->_waitCondition.wait(this->_mutex);
        }

    }
}
