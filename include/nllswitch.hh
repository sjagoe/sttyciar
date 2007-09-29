#ifndef __NLLSWITCH_HH__
#define __NLLSWITCH_HH__

#include "networklogiclayer.hh"
#include "maclookup.hh"

class NLLSwitch: public NetworkLogicLayer
{
    public:
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
        MACLookup _lookupTable; //! The MAC Address Lookup table
};

#endif
