#include "statistics.hh"

Statistics::Statistics(shared_ptr<QMap<shared_ptr<Device>,QMap<shared_ptr<Device>,double> > >& traffic,
                       int totalPackets)
{
    this->_percentageTraffic.reset(new QMap<shared_ptr<Device>,QMap<shared_ptr<Device>,double> >());
    this->calculateTrafficPercentage(traffic,totalPackets);
}

double Statistics::getTrafficPercentage(shared_ptr<Device> source, shared_ptr<Device> destination)
{
    QMap<shared_ptr<Device>,double> sourceRow = this->_percentageTraffic->value(source);
    return sourceRow.value(destination);
}

int Statistics::getTotalPackets() const
{
    return this->_totalPackets;
}

void Statistics::calculateTrafficPercentage(shared_ptr<QMap<shared_ptr<Device>,QMap<shared_ptr<Device>,double> > >& traffic,
                                               int totalPackets)
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
        this->_totalPackets = totalPackets;
    }
}
