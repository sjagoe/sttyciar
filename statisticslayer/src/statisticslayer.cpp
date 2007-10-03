#include "statisticslayer.hh"
#include "interfaceroute.hh"
#include "statistics.hh"
#include "rawpacket.hh"
#include "packetdumper.hh"

StatisticsLayer::StatisticsLayer(QList<shared_ptr<Device> >& activatedDevices, weak_ptr<PacketDumper>& dumper)
{
    this->_running = false;
    this->initializeTable(activatedDevices);
    this->_packetDumper = dumper;
}

void StatisticsLayer::addRawPacket(const shared_ptr<RawPacket>& rawPacket)
{
    this->_statisticsQueue.push(rawPacket);
    this->_waitCondition.wakeAll();
}

void StatisticsLayer::reset()
{
    for (QMap<shared_ptr<Device>, QMap<shared_ptr<Device>, double> >::iterator iter=this->_traffic->begin(); iter!=this->_traffic->end(); iter++)
    {
        for (QMap<shared_ptr<Device>,double>::iterator iter2=iter->begin(); iter2!=iter->end(); iter2++)
        {
            *iter2 = 0;
        }
    }
    this->_totalPackets = 0;
    this->_totalBytes = 0;
}

/*shared_ptr<Statistics> StatisticsLayer::getStatistics()
{
    shared_ptr<Statistics> statistics(new Statistics(this->_traffic,this->_totalPackets));
    this->clearTable();
    return statistics;
}*/

std::string StatisticsLayer::toString()
{
    this->_mutex.lock();

    ostringstream osstream;
    for (QMap<shared_ptr<Device>, QMap<shared_ptr<Device>, double> >::const_iterator iter=this->_traffic->begin(); iter!=this->_traffic->end(); iter++)
    {
        for (QMap<shared_ptr<Device>,double>::const_iterator iter2=iter->begin(); iter2!=iter->end(); iter2++)
        {
            osstream << (*iter2) << " ";
        }
        osstream << std::endl;
    }
    return osstream.str();

    this->_mutex.unlock();
}

void StatisticsLayer::stopRunning()
{
    this->_running = false;
    this->_waitCondition.wakeAll();
    this->wait();
}

void StatisticsLayer::run()
{
    this->_running = true;

    shared_ptr<RawPacket> rawPacket;
    while (this->_running)
    {
        if (!this->_statisticsQueue.isEmpty())
        {
            this->_statisticsQueue.pop(rawPacket);
            shared_ptr<PacketDumper> dumper = this->_packetDumper.lock();
            if (dumper.get() != 0)
            {
                dumper->savePacket(rawPacket);
            }
            this->_mutex.lock();
            this->updateStatistics(rawPacket);
            this->_mutex.unlock();
        }
        else
        {
            this->_mutex.lock();
            this->_waitCondition.wait(&this->_mutex);
            this->_mutex.unlock();
        }
    }
}

void StatisticsLayer::initializeTable(const QList<shared_ptr<Device> >& activatedDevices)
{
    this->_traffic.reset(new QMap<shared_ptr<Device>, QMap<shared_ptr<Device>, double> >);
    for (QList<shared_ptr<Device> >::const_iterator iter = activatedDevices.begin(); iter != activatedDevices.end(); iter++)
    {
        QMap<shared_ptr<Device>, double> temp;
        for (QList<shared_ptr<Device> >::const_iterator iter2 = activatedDevices.begin(); iter2 != activatedDevices.end(); iter2++)
        {
            if (iter != iter2)
                temp.insert(*iter2,0);
        }
        this->_traffic->insert(*iter,temp);
    }

    this->_totalPackets = 0;
    this->_totalBytes = 0;
}

void StatisticsLayer::updateStatistics(const shared_ptr<RawPacket>& rawPacket)
{
    QMap<shared_ptr<Device>,double> sourceRow = this->_traffic->value(rawPacket->getInterfaceRoute()->getSource());
    shared_ptr<QList<shared_ptr<Device> > > destinationDevices = rawPacket->getInterfaceRoute()->getDestinations();

    for (QList<shared_ptr<Device> >::const_iterator iter=destinationDevices->begin(); iter != destinationDevices->end(); iter++)
    {
        sourceRow.insert(*iter,sourceRow.value(*iter)+1);
    }

    this->_traffic->insert(rawPacket->getInterfaceRoute()->getSource(),sourceRow);

    this->_totalPackets += destinationDevices->size();

    /*the amount of bytes equals the packets size in bytes multiplied by the amount of devices
    that the packet is being sent to*/
    this->_totalBytes += ((rawPacket->getPacketLength())*(destinationDevices->size()));
}

void StatisticsLayer::calculate(int timePeriodMillis)
{
    this->_mutex.lock();

    shared_ptr<Statistics> statistics(new Statistics(this->_traffic,
                                      this->_totalPackets,this->_totalBytes,
                                      timePeriodMillis));
    this->reset();
    emit sendStats(statistics);

    this->_mutex.unlock();
}

