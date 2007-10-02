#include "statisticslayer.hh"
#include "interfaceroute.hh"
#include "statistics.hh"
#include "rawpacket.hh"

StatisticsLayer::StatisticsLayer()
{

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
    this->_totalBytes += rawPacket->getPacketLength();

}

void StatisticsLayer::initializeTable(QList<shared_ptr<Device> >& devices)
{
    this->_traffic.reset(new QMap<shared_ptr<Device>, QMap<shared_ptr<Device>, double> >);
    for (QList<shared_ptr<Device> >::const_iterator iter = devices.begin(); iter != devices.end(); iter++)
    {
        QMap<shared_ptr<Device>, double> temp;
        for (QList<shared_ptr<Device> >::const_iterator iter2 = devices.begin(); iter2 != devices.end(); iter2++)
        {
            if (iter != iter2)
                temp.insert(*iter2,0);
        }
        this->_traffic->insert(*iter,temp);
    }

    this->_totalPackets = 0;
    this->_totalBytes = 0;
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
}

void StatisticsLayer::calculate(int timePeriodMillis)
{
    shared_ptr<Statistics> statistics(new Statistics(this->_traffic,
                                      this->_totalPackets,this->_totalBytes,
                                      timePeriodMillis));
    this->reset();
    emit sendStats(statistics);
}
