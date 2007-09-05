#ifndef __ETHERNETIIFRAME_HH__
#define __ETHERNETIIFRAME_HH__


#include <sys/types.h>
#include <vector>

#include <boost/array.hpp>

#include "defines.hh"

using std::vector;
using boost::array;

class Packet;

#define ETHERNETII_MAC_LENGTH 6
#define ETEHRNETII_ETHERTYPE_LENGTH 2

/*!
EthernetIIFrame encapsulates the Ethernet II Frame header and
payload with an easy to use interface.

The EthernetIIFrame should be created with a Packet as an argument.
It will take its data from the raw packet data.

@author Simon Jagoe
*/

class EthernetIIFrame
{
    public:
        EthernetIIFrame();
        EthernetIIFrame( Packet& packet );

        inline const array<u_char, ETHERNETII_MAC_LENGTH>& getSourceMAC()
        {
            return sourceMAC;
        };

        inline const array<u_char, ETHERNETII_MAC_LENGTH>& getDestinationMAC()
        {
            return destinationMAC;
        };

        inline const array<u_char, ETEHRNETII_ETHERTYPE_LENGTH>& getEtherType()
        {
            return etherType;
        };

        inline const vector<u_char>& getPayload()
        {
            return payload;
        };

    private:
        array<u_char, ETHERNETII_MAC_LENGTH> sourceMAC;
        array<u_char, ETHERNETII_MAC_LENGTH> destinationMAC;
        array<u_char, ETEHRNETII_ETHERTYPE_LENGTH> etherType;

        vector<u_char> payload;
};

#endif
