#include "statisticslayer.hh"

StatisticsLayer::StatisticsLayer()
{

}

void StatisticsLayer::updateStatistics( InterfaceRoute& interfaces )
{

}

void StatisticsLayer::availableInterfaces( list<shared_ptr<Device> >& devices )
{
    list<shared_ptr<Device> >::const_iterator main_iter = devices.begin();
    list<shared_ptr<Device> >::const_iterator secondary_iter = devices.begin();

    for (; main_iter != devices.end(); main_iter++)
    {
        QMap<shared_ptr<Device>, long long> temp;
        for (; secondary_iter != devices.end(); secondary_iter++)
        {
            if (main_iter != secondary_iter)
                temp.insert( *secondary_iter, 0 );
        }
        _traffic.insert( *main_iter, temp );
    }
}
