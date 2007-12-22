#include "pcapsendthread.hh"
#include "rawpacket.hh"

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
    this->_packetQueue.push(packet);
    this->_mutex.lock();
    this->_mutex.unlock();
    this->_waitCondition.wakeAll();
}

void PcapSendThread::stopRunning()
{
    this->_running = false;
    this->_mutex.lock();
    this->_mutex.unlock();
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
            pcap_sendpacket(this->_pcapDevice,rawPacket->getPacketPointer(),rawPacket->getPacketLength());
        }
        else
        {
            this->_mutex.lock();
            this->_waitCondition.wait(&this->_mutex);
            //this->_mutex.unlock();
        }

    }
    std::cout << "\nsend: finish - thread number: " << thread_number << std::endl;
    //pcap_close(source);
}
