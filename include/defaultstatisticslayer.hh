#ifndef __DEFAULTSTATISTICSLAYER_HH__
#define __DEFAULTSTATISTICSLAYER_HH__

#include "alstatisticslistener.hh"

class DefaultStatisticsLayer : public ALStatisticsListener
{
    public:
        inline DefaultStatisticsLayer(){}
        inline ~DefaultStatisticsLayer(){}
        inline void updateStatistics(shared_ptr<InterfaceRoute>& interfaces ){}
        inline void initializeTable( QList<shared_ptr<Device> >& devices ){}
};

#endif // __DEFAULTSTATISTICSLAYER_HH__
