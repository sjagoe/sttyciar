#include "pcapthread.hh"

PcapThread::PcapThread()
{
}

PcapThread::PcapThread(const shared_ptr<Device>& device)
{
    this->_device=device;
}

PcapThread::~PcapThread()
{
}

void PcapThread::run()
{

}
