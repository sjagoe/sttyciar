#ifndef __ALSTATISTICSLISTENER_HH__
#define __ALSTATISTICSLISTENER_HH__

class InterfaceRoute;

/*!
The ALStatisticsListener is a (pure virtual) public interface that must be
implemented by the StatisticsLayer to make statistical data available to the
user.

@author Simon Jagoe
*/
class ALStatisticsListener
{
    public:
        /*!
        A method to send raw usage data to the SL for processing.

        The SL processes the data received through this method, and passes the
        processed information to the user interface for displaying.

        @param interfaces The InterfaceRoute object passed to the AL after
        routing, containing complete source/destination interface data.
        */
        virtual void updateStatistics( InterfaceRoute& interfaces ) = 0;

        /*!
        A method to pass all available network interfaces to the user interface
        to allow users to easily configure the routing infrastructure.
        */
        virtual void availableInterfaces( /* device linked list */ ) = 0;
};

#endif
