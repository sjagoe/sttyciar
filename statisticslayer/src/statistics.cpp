#include "statistics.hh"

Statistics::Statistics(shared_ptr<QMap<shared_ptr<Device>,QMap<shared_ptr<Device>,double> > >& traffic,
                       unsigned int totalPackets,unsigned int totalBytes,unsigned int timePeriodMillis)
{
    this->_percentageTraffic.reset(new QMap<shared_ptr<Device>,QMap<shared_ptr<Device>,double> >());
    this->calculateTrafficPercentage(traffic,totalPackets);
    this->calculateRates(totalPackets,totalBytes,timePeriodMillis);
}

double Statistics::getTrafficPercentage(shared_ptr<Device> source, shared_ptr<Device> destination)
{
    QMap<shared_ptr<Device>,double> sourceRow = this->_percentageTraffic->value(source);
    return sourceRow.value(destination);
}

/*int Statistics::getTotalPackets() const
{
    return this->_totalPackets;
}*/


double Statistics::getPacketsPerSecond()
{
    return this->_packetsPerSecond;
}

double Statistics::getBytesPerSecond()
{
    return this->_bytesPerSecond;
}

void Statistics::calculateTrafficPercentage(shared_ptr<QMap<shared_ptr<Device>,QMap<shared_ptr<Device>,double> > >& traffic,
                                            unsigned int totalPackets)
{
    for (QMap<shared_ptr<Device>, QMap<shared_ptr<Device>, double> >::const_iterator iter=traffic->begin(); iter!=traffic->end(); iter++)
    {
        QMap<shared_ptr<Device>,double> sourceRow;
        for (QMap<shared_ptr<Device>,double>::const_iterator iter2=iter->begin(); iter2!=iter->end(); iter2++)
        {
            //calculation is done here
            sourceRow.insert(iter2.key(),iter2.value()/(double)totalPackets);
        }
        this->_percentageTraffic->insert(iter.key(),sourceRow);
        //this->_totalPackets = totalPackets;
    }
}

void Statistics::calculateRates(unsigned int totalPackets,unsigned int totalBytes,unsigned int timePeriodMillis)
{
    this->_bytesPerSecond = (((double)totalBytes)/((double)timePeriodMillis))*1000;
    this->_packetsPerSecond = (((double)totalPackets)/((double)timePeriodMillis))*1000;
}

