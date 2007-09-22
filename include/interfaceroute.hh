#ifndef __INTERFACEROUTE_HH__
#define __INTERFACEROUTE_HH__

// STL
#include <QList>

// boost
#include <boost/shared_ptr.hpp>

// local
//#include "device.hh"

using std::list;
using boost::shared_ptr;

// forward declerations
class Device;

/*!
InterfaceRoute contains a source device, used by the NLL to help determine a
route, and a list of destination devices, used by the AL to identify which
devices to use to transmit a packet.

\author Simon Jagoe
*/
class InterfaceRoute
{
    private:
        shared_ptr<Device> _sourceInterface;
        shared_ptr<QList<shared_ptr<Device> > > _destinationInterfaces;

    public:
        InterfaceRoute();
        /*!
        Create an InterfaceRoute with a specified source device.

        The only time a source device can be set is at creation time (i.e.
        the source cannot be modified in the NLL).
        */
        InterfaceRoute( const shared_ptr<Device>& sourceInterface );

        void setSource( const shared_ptr<Device>& sourceInterface );

        /*!
        Add a destination to the list of destination devices.
        */
        void addDestination( const shared_ptr<Device>& destinationInterface );

        /*!
        Remove all destinations from the list.
        */
        void clearDestinations();

        /*!
        Return the list of destination Devices.
        */
        inline const shared_ptr<QList<shared_ptr<Device> > >& getDestinations() const
        {
            return _destinationInterfaces;
        };

        /*!
        Return the source Device.
        */
        inline const shared_ptr<Device>& getSource() const
        {
            return _sourceInterface;
        };
};

#endif
