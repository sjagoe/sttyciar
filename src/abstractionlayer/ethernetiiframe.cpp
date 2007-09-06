#include <ext/algorithm>

#include "ethernetiiframe.hh"
#include "rawpacket.hh"

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

EthernetIIFrame::EthernetIIFrame( RawPacket& packet )
{
    vector<u_char> data = packet.getPacket();

    vector<u_char>::const_iterator iter = data.begin();

    std::pair<vector<u_char>::const_iterator,
        array<u_char, ETHERNETII_MAC_LENGTH>::iterator > resultLocations =
        __gnu_cxx::copy_n(data.begin(), ETHERNETII_MAC_LENGTH,
        sourceMAC.begin());

    resultLocations =
        __gnu_cxx::copy_n(resultLocations.first, ETHERNETII_MAC_LENGTH,
        destinationMAC.begin());

    resultLocations =
        __gnu_cxx::copy_n(resultLocations.first, ETEHRNETII_ETHERTYPE_LENGTH,
        etherType.begin());

    payload.resize(packet.getPacketLength() - ETHERNETII_HEAD_LENGTH);

    __gnu_cxx::copy_n(resultLocations.first,
        (packet.getPacketLength() - ETHERNETII_HEAD_LENGTH), payload.begin());
}
