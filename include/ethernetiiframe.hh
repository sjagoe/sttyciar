#ifndef __ETHERNETIIFRAME_HH__
#define __ETHERNETIIFRAME_HH__


#include <sys/types.h>
#include <vector>

#include <boost/array.hpp>

#include "defines.hh"

#include "packet.hh"

using std::vector;
using boost::array;

class RawPacket;

#define ETHERNETII_MAC_LENGTH 6
#define ETEHRNETII_ETHERTYPE_LENGTH 2

/*!
EthernetIIFrame encapsulates the Ethernet II Frame header and payload with an
easy to use interface.

The EthernetIIFrame should be created with a RawPacket as an argument. It will
extract the Ethernet II header and payload from the raw packet data.

@author Simon Jagoe
*/

class EthernetIIFrame: public Packet
{
    public:
//        /*!
//        Default constructor: zeros all member variables.
//        */
//        EthernetIIFrame();

        /*!
        Preferred constructor: extract the header information and payload from
        a RawPacket object.

        @param packet The Packet object containing the raw packet data
        */
        EthernetIIFrame( RawPacket& packet );

        RawPacket getRawPacket();


        inline const array<u_char, ETHERNETII_MAC_LENGTH>& getSourceMAC()
        {
            return _sourceMAC;
        };

        inline const array<u_char, ETHERNETII_MAC_LENGTH>& getDestinationMAC()
        {
            return _destinationMAC;
        };

        inline const array<u_char, ETEHRNETII_ETHERTYPE_LENGTH>& getEtherType()
        {
            return _etherType;
        };

        inline const vector<u_char>& getPayload()
        {
            return _payload;
        };

    private:
        array<u_char, ETHERNETII_MAC_LENGTH>       _sourceMAC;
        array<u_char, ETHERNETII_MAC_LENGTH>       _destinationMAC;
        array<u_char, ETEHRNETII_ETHERTYPE_LENGTH> _etherType;

        vector<u_char> _payload;
};

#endif
