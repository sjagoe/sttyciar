#include <ext/algorithm>

#include "ethernetiiframe.hh"
#include "packet.hh"

EthernetIIFrame::EthernetIIFrame()
{
    sourceMAC[0] = 0;
    sourceMAC[1] = 0;
    sourceMAC[2] = 0;
    sourceMAC[3] = 0;
    sourceMAC[4] = 0;
    sourceMAC[5] = 0;
    destinationMAC[0] = 0;
    destinationMAC[1] = 0;
    destinationMAC[2] = 0;
    destinationMAC[3] = 0;
    destinationMAC[4] = 0;
    destinationMAC[5] = 0;
    etherType[0] = 0;
    etherType[1] = 0;
}

EthernetIIFrame::EthernetIIFrame( Packet& packet )
{
    vector<u_char> data = packet.getPacket();
    vector<u_char>::const_iterator iter = data.begin();
    //__gnu_cxx::copy_n(
}
