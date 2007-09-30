#ifndef __DEFAULTSTATISTICSLAYER_HH__
#define __DEFAULTSTATISTICSLAYER_HH__

#include <QtCore>
#include "boost/shared_ptr.hpp"
#include "alstatisticslistener.hh"


using boost::shared_ptr;

class Device;
class RawPacket;
/*!
A default implementation of the ALStatisticsListener. This is here for efficiency purposes:
It is possbile use the AbstractionLayer without statistics collection. This default implementation
just ensures that no statistics processing occurs when a packet is sent, effectively avoiding an
if-statement which would ask after every packet whether statistics should be collected.

\author Doron Horwitz
*/
class DefaultStatisticsLayer : public ALStatisticsListener
{
    public:
        /*!
        Default constructor
        */
        inline DefaultStatisticsLayer(){}

        /*!
        Destructor
        */
        inline ~DefaultStatisticsLayer(){}

        /*!
        See declaration of ALStatisticsListener::updateStatistics(shared_ptr<InterfaceRoute>&)
        */
        inline void updateStatistics(const shared_ptr<RawPacket>& rawPacket ){}

        /*!
        See declaration of ALStatisticsListener::initializeTable(QList<shared_ptr<Device> >&)
        */
        inline void initializeTable( QList<shared_ptr<Device> >& devices ){}
};

#endif // __DEFAULTSTATISTICSLAYER_HH__
