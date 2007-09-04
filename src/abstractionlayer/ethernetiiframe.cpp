#include "ethernetiiframe.hh"

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
    nextType[0] = 0;
    nextType[1] = 0;
}
