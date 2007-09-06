#include <ext/algorithm>

#include "ethernetiiframe.hh"
#include "rawpacket.hh"

//EthernetIIFrame::EthernetIIFrame()
//{
//    _sourceMAC[0] = 0;
//    _sourceMAC[1] = 0;
//    _sourceMAC[2] = 0;
//    _sourceMAC[3] = 0;
//    _sourceMAC[4] = 0;
//    _sourceMAC[5] = 0;
//    _destinationMAC[0] = 0;
//    _destinationMAC[1] = 0;
//    _destinationMAC[2] = 0;
//    _destinationMAC[3] = 0;
//    _destinationMAC[4] = 0;
//    _destinationMAC[5] = 0;
//    _etherType[0] = 0;
//    _etherType[1] = 0;
//}

void EthernetIIFrame::setData( RawPacket& packet )
{
    vector<u_char> data = packet.getPacket();

    vector<u_char>::const_iterator iter = data.begin();

    std::pair<vector<u_char>::const_iterator,
        array<u_char, ETHERNETII_MAC_LENGTH>::iterator > resultLocations =
        __gnu_cxx::copy_n(data.begin(), ETHERNETII_MAC_LENGTH,
        _sourceMAC.begin());

    resultLocations =
        __gnu_cxx::copy_n(resultLocations.first, ETHERNETII_MAC_LENGTH,
        _destinationMAC.begin());

    resultLocations =
        __gnu_cxx::copy_n(resultLocations.first, ETEHRNETII_ETHERTYPE_LENGTH,
        _etherType.begin());

    _payload.resize(packet.getPacketLength() - ETHERNETII_HEAD_LENGTH);

    __gnu_cxx::copy_n(resultLocations.first,
        (packet.getPacketLength() - ETHERNETII_HEAD_LENGTH), _payload.begin());
}

RawPacket EthernetIIFrame::getRawPacket()
{
    RawPacket raw;

    vector<u_char> temp(_sourceMAC.begin(), _sourceMAC.end());

    raw.append( temp );

    temp.clear();

    temp.insert( temp.begin(), _destinationMAC.begin(), _destinationMAC.end() );

    raw.append( temp );

    temp.clear();

    temp.insert( temp.begin(), _etherType.begin(), _etherType.end() );

    raw.append( temp );

    raw.append( _payload );

    return raw;
}
