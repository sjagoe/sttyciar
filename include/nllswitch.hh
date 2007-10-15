#ifndef __NLLSWITCH_HH__
#define __NLLSWITCH_HH__

#include "networklogiclayer.hh"
#include "maclookup.hh"

/*!
The subclass of NetworkLogicLayer that provides an implementation of an
Ethernet Switch.

\author Simon Jagoe
*/
class NLLSwitch: public NetworkLogicLayer
{
    public:
        /*!
        Empty constructor that calls the constructor of the base class.
        */
        NLLSwitch()
            : NetworkLogicLayer()
        {};

    public slots:
        /*!
        Timed event.

        \see NetworkLogicLayer
        */
        void update( int millisecondsElapsed );

    protected:
        /*!
        Overridden routPacket() method. \see NetworkLogicLayer.

        This provides the logic necessary for a Switch implementation.
        */
        void routePacket( shared_ptr<RawPacket>& packet );

    private:
        //! The MAC Address Lookup table
        MACLookup _lookupTable;
};

#endif
