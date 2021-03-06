#ifndef __ALSTATISTICSLISTENER_HH__
#define __ALSTATISTICSLISTENER_HH__

#include <boost/shared_ptr.hpp>

#include <QList>

using boost::shared_ptr;
using std::list;

class RawPacket;
class Device;

/*!
The ALStatisticsListener is a (pure virtual) public interface that must be
implemented by the StatisticsLayer to make statistical data available to the
user.

\author Simon Jagoe
*/
class ALStatisticsListener
{
    public:
        /*!
        Virtual destructor to allow destructor overriding.
        */
        virtual ~ALStatisticsListener() {};

        /*!
        A method to send raw usage data to the SL for processing.

        The SL processes the data received through this method, and passes the
        processed information to the user interface for displaying.

        \param rawPacket The packet that has been processed by the NLL.
        */
        virtual void addRawPacket(const shared_ptr<RawPacket>& rawPacket ) = 0;

        /* !
        A method to pass all available network interfaces to the user interface
        to allow users to easily configure the routing infrastructure.
        */
        //virtual void initializeTable( QList<shared_ptr<Device> >& devices ) = 0;
};

#endif
