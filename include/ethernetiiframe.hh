#ifndef __ETHERNETIIFRAME_HH__
#define __ETHERNETIIFRAME_HH__

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
        EthernetIIFrame( Packet& packet );

    private:
        u_char[6] sourceMAC;
        u_char[6] destinationMAC;
        u_char[2] nextType;
};

#endif
