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

// forward declarations
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
        shared_ptr<Device> _sourceInterface; //! The interface that the associated packet was received on (Objects of this classreside in the associated RawPacket)
        shared_ptr<QList<shared_ptr<Device> > > _destinationInterfaces; //! interfaces that the associated packet will be transmitted on

    public:
        /*!
        Create an InterfaceRoute with empty source and destination interfaces.
        */
        InterfaceRoute();
        /*!
        Create an InterfaceRoute with a specified source device.

        \param sourceInterface The Device to store as the packet's source.
        */
        InterfaceRoute( const shared_ptr<Device>& sourceInterface );

        /*!
        Set a source interface.

        \param sourceInterface The Device to store as the packet's source.
        */
        void setSource( const shared_ptr<Device>& sourceInterface );

        /*!
        Add a destination to the list of destination devices.

        \param destinationInterface The Device to add to the list of destination
        interfaces.
        */
        void addDestination( const shared_ptr<Device>& destinationInterface );

        /*!
        Remove all destinations from the list.
        */
        void clearDestinations();

        /*!
        Return the list of destination Devices.

        \return QList of destination devices
        */
        inline const shared_ptr<QList<shared_ptr<Device> > >& getDestinations() const
        {
            return _destinationInterfaces;
        };

        /*!
        Return the source Device.

        \return Source device
        */
        inline const shared_ptr<Device>& getSource() const
        {
            return _sourceInterface;
        };
};

#endif
