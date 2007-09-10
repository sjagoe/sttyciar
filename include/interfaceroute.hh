#ifndef __INTERFACEROUTE_HH__
#define __INTERFACEROUTE_HH__

#include <vector>
#include <string>

using std::vector;
using std::string;

/*!
InterfaceRoute contains a source device, used by the NLL to help determine a
route, and a list of destination devices, used by the AL to identify which
devices to use to transmit a packet.

@author Simon Jagoe
*/
class InterfaceRoute
{
    private:
        string _sourceInterface;
        vector<string> _destinationInterfaces;

    public:
        /*!
        Create an InterfaceRoute with a specified source device.

        The only time a source device can be set is at creation time (i.e.
        the source cannot be modified in the NLL).
        */
        InterfaceRoute(/* source device */);

        /*!
        Add a destination to the list of destination devices.
        */
        void addDestination();

        /*!
        Remove all destinations from the list.
        */
        void clearDestinations();

        /*!
        Set the list of destinations to a precompiled list (rather than
        appending one by one).
        */
        void setDestinations();

        /*!
        Return the list of destination Devices.
        */
        inline const vector<string>& getDestinations() const
        {
            return _destinationInterfaces;
        };

        /*!
        Return the source Device.
        */
        inline const string& getSource() const
        {
            return _sourceInterface;
        };
};

#endif
