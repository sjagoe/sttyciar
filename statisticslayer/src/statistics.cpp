//#include <iostream>
#include "statistics.hh"

Statistics::Statistics(shared_ptr<QMap<shared_ptr<Device>,QMap<shared_ptr<Device>,double> > >& traffic,
                       shared_ptr<QMap<shared_ptr<Device>,QMap<shared_ptr<Device>,double> > >& trafficBytes,
                       unsigned int totalPackets,unsigned int totalBytes,unsigned int timePeriodMillis,
                       int awaitingDumpedPackets)
{
    this->calculateTrafficPercentage(traffic,totalPackets);
    this->calculateRates(trafficBytes,totalPackets,totalBytes,timePeriodMillis);

    this->_amtPacketsTraffic.reset(new QMap<shared_ptr<Device>,QMap<shared_ptr<Device>,double> >( *traffic ) );
//    this->_amtPacketsTraffic = traffic;


    this->_awaitingDumpedPackets = awaitingDumpedPackets;
}

double Statistics::getTrafficPercentage(shared_ptr<Device> source, shared_ptr<Device> destination)
{
    QMap<shared_ptr<Device>,double> sourceRow = this->_percentageTraffic->value(source);
    return sourceRow.value(destination);
}

shared_ptr<QMap<shared_ptr<Device>,QMap<shared_ptr<Device>,double> > > Statistics::getTrafficPercentageTable()
{
    return this->_percentageTraffic;
}

shared_ptr<QMap<shared_ptr<Device>,QMap<shared_ptr<Device>,double> > > Statistics::getTrafficAmtPacketsTable()
{
//    QMap<shared_ptr<Device>,QMap<shared_ptr<Device>,double> >::const_iterator iter = this->_amtPacketsTraffic->begin();
//    for (; iter != this->_amtPacketsTraffic->end(); iter++)
//    {
//        QMap<shared_ptr<Device>,double>::const_iterator iter1 = iter.value().begin();
//        for (; iter1 != iter.value().end(); iter1++)
//        {
//            std::cout << iter1.value() << " ";
//        }
//    }
//    std::cout << std::endl << std::endl;
    return this->_amtPacketsTraffic;
}

shared_ptr<QMap<shared_ptr<Device>,QMap<shared_ptr<Device>,double> > > Statistics::getTrafficAmtBytesPerSecondTable()
{
    return this->_amtBytesPerSecondTraffic;
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

int Statistics::getAwaitingDumpedPackets()
{
    return this->_awaitingDumpedPackets;
}
void Statistics::calculateTrafficPercentage(shared_ptr<QMap<shared_ptr<Device>,QMap<shared_ptr<Device>,double> > >& traffic,
                                            unsigned int totalPackets)
{
    this->_percentageTraffic.reset(new QMap<shared_ptr<Device>,QMap<shared_ptr<Device>,double> >());
    for (QMap<shared_ptr<Device>, QMap<shared_ptr<Device>, double> >::const_iterator iter=traffic->begin(); iter!=traffic->end(); iter++)
    {
        QMap<shared_ptr<Device>,double> sourceRow;
        if (totalPackets != 0)
        {

            for (QMap<shared_ptr<Device>,double>::const_iterator iter2=iter->begin(); iter2!=iter->end(); iter2++)
            {
                //calculation is done here
                sourceRow.insert(iter2.key(),iter2.value()/(double)totalPackets);
            }
        }
        else
        {
            for (QMap<shared_ptr<Device>,double>::const_iterator iter2=iter->begin(); iter2!=iter->end(); iter2++)
            {
                //should this 0's source row be created repeatedly here? Inefficient!
                sourceRow.insert(iter2.key(),(double)0);
            }
        }
        //this->_totalPackets = totalPackets;
        this->_percentageTraffic->insert(iter.key(),sourceRow);
    }
}

void Statistics::calculateRates(shared_ptr<QMap<shared_ptr<Device>,QMap<shared_ptr<Device>,double> > >& trafficBytes,
                        unsigned int totalPackets,unsigned int totalBytes,unsigned int timePeriodMillis)
{
    this->_amtBytesPerSecondTraffic.reset(new QMap<shared_ptr<Device>,QMap<shared_ptr<Device>,double> >() );

    for (QMap<shared_ptr<Device>, QMap<shared_ptr<Device>, double> >::const_iterator iter=trafficBytes->begin(); iter!=trafficBytes->end(); iter++)
    {
        QMap<shared_ptr<Device>,double> sourceRow;
        if (timePeriodMillis != 0)
        {

            for (QMap<shared_ptr<Device>,double>::const_iterator iter2=iter->begin(); iter2!=iter->end(); iter2++)
            {
                //calculation is done here
                sourceRow.insert(iter2.key(),iter2.value()/(double)timePeriodMillis*1000);
            }
        }
        else
        {
            for (QMap<shared_ptr<Device>,double>::const_iterator iter2=iter->begin(); iter2!=iter->end(); iter2++)
            {
                //should this 0's source row be created repeatedly here? Inefficient!
                sourceRow.insert(iter2.key(),(double)0);
            }
        }
        this->_amtBytesPerSecondTraffic->insert(iter.key(),sourceRow);
    }

    this->_bytesPerSecond = (((double)totalBytes)/((double)timePeriodMillis))*1000;
    this->_packetsPerSecond = (((double)totalPackets)/((double)timePeriodMillis))*1000;
}

