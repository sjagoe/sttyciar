#ifndef __INTERFACEROUTE_HH__
#define __INTERFACEROUTE_HH__

// STL
#include <list>

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

@author Simon Jagoe
*/
class InterfaceRoute
{
    private:
        shared_ptr<Device> _sourceInterface;
        list<shared_ptr<Device> > _destinationInterfaces;

    public:
        /*!
        Create an InterfaceRoute with a specified source device.

        The only time a source device can be set is at creation time (i.e.
        the source cannot be modified in the NLL).
        */
        InterfaceRoute( shared_ptr<Device>& sourceInterface );

        /*!
        Add a destination to the list of destination devices.
        */
        void addDestination( const shared_ptr<Device>& destinationInterface );

        /*!
        Remove all destinations from the list.
        */
        void clearDestinations();

        /* !
        Set the list of destinations to a precompiled list (rather than
        appending one by one).
        */
        //void setDestinations();

        /*!
        Return the list of destination Devices.
        */
        inline const list<shared_ptr<Device> >& getDestinations() const
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
