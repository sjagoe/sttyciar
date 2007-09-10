#ifndef __ALSTATISTICSLISTENER_HH__
#define __ALSTATISTICSLISTENER_HH__

class InterfaceRoute;

class ALStatisticsListener
{
    public:
        virtual void updateStatistics( InterfaceRoute& interfaces ) = 0;
        virtual void availableInterfaces( /* device linked list */ ) = 0;
};

#endif
