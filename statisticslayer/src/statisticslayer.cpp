#include "statisticslayer.hh"
#include "interfaceroute.hh"
//#include "device.hh"

StatisticsLayer::StatisticsLayer()
{

}

void StatisticsLayer::updateStatistics(InterfaceRoute& interfaceRoute)
{
    QMap<shared_ptr<Device>,double> sourceRow = this->_traffic.value(interfaceRoute.getSource());
    shared_ptr<QList<shared_ptr<Device> > >destinationDevices = interfaceRoute.getDestinations();

    for (QList<shared_ptr<Device> >::const_iterator iter=destinationDevices->begin(); iter != destinationDevices->end(); iter++)
    {
        sourceRow.insert(*iter,sourceRow.value(*iter)+1);
    }

    this->_traffic.insert(interfaceRoute.getSource(),sourceRow);
}

void StatisticsLayer::initializeTable(QList<shared_ptr<Device> >& devices)
{
    for (QList<shared_ptr<Device> >::const_iterator iter = devices.begin(); iter != devices.end(); iter++)
    {
        QMap<shared_ptr<Device>, double> temp;
        for (QList<shared_ptr<Device> >::const_iterator iter2 = devices.begin(); iter2 != devices.end(); iter2++)
        {
            if (iter != iter2)
                temp.insert(*iter2,0);
        }
        this->_traffic.insert(*iter,temp);
    }
}

void StatisticsLayer::clearTable()
{
    for (QMap<shared_ptr<Device>, QMap<shared_ptr<Device>, double> >::iterator iter=this->_traffic.begin(); iter!=this->_traffic.end(); iter++)
    {
        for (QMap<shared_ptr<Device>,double>::iterator iter2=iter->begin(); iter2!=iter->end(); iter2++)
        {
            *iter2 = 0;
        }
    }
}

std::string StatisticsLayer::toString()
{
    ostringstream osstream;
    for (QMap<shared_ptr<Device>, QMap<shared_ptr<Device>, double> >::const_iterator iter=this->_traffic.begin(); iter!=this->_traffic.end(); iter++)
    {
        //osstream << iter.key()->getName();
        for (QMap<shared_ptr<Device>,double>::const_iterator iter2=iter->begin(); iter2!=iter->end(); iter2++)
        {
            osstream << (*iter2) << " ";
        }
        osstream << std::endl;
    }
    return osstream.str();
}
