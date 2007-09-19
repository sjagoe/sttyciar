#include "pcapsendthread.hh"
#include "rawpacket.hh"

PcapSendThread::PcapSendThread()
{
    this->_running = false;
}

PcapSendThread::PcapSendThread(const string& deviceName)
{
    this->_running = false;
    this->_deviceName = deviceName;
}

PcapSendThread::~PcapSendThread()
{
}

void PcapSendThread::setDeviceName(const string& deviceName)
{
    this->_deviceName = deviceName;
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
    pcap_t* source=NULL;
    this->_running = true;
    if ((source=pcap_open_live(this->_deviceName.c_str(),65535,true,3000,this->_pcapErrorBuffer))==NULL)
        this->_running = false;

    shared_ptr<RawPacket> rawPacket;
    while (this->_running)
    {
        if (!this->_packetQueue.isEmpty())
        {
            _packetQueue.pop(rawPacket);
            pcap_sendpacket(source,rawPacket->getPacketPointer(),rawPacket->getPacketLength());
        }
        else
        {
            this->_mutex.lock();
            this->_waitCondition.wait(&this->_mutex,ULONG_MAX);
            this->_mutex.unlock();
        }

    }
    pcap_close(source);
}
