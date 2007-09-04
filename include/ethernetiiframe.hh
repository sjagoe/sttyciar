#ifndef __ETHERNETIIFRAME_HH__
#define __ETHERNETIIFRAME_HH__


#include <sys/types.h>
#include <vector>

//#include "defines.hh"

class Packet;

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
        //EthernetIIFrame( Packet& packet );

    private:
        u_char sourceMAC[6];
        u_char destinationMAC[6];
        u_char nextType[2];

        std::vector<u_char> payload;
};

#endif
