#include <ext/algorithm>

#include "ethernetiiframe.hh"
#include "rawpacket.hh"

const int EthernetIIFrame::ETHERNETII_HEAD_LENGTH;
const int EthernetIIFrame::ETHERNETII_MAC_LENGTH;

EthernetIIFrame::EthernetIIFrame( shared_ptr<RawPacket>& packet )
    : DataLinkLayerPacket( packet )
{
    _sourceMAC = (mac_t*) _rawPacket.get();
    _destMAC = (mac_t*) (_rawPacket.get() + ETHERNETII_MAC_LENGTH);
    _etherType = (ethertype_t*) _rawPacket.get() + 2*ETHERNETII_MAC_LENGTH;
}

const int EthernetIIFrame::getPayloadOffset() const
{
    return ETHERNETII_HEAD_LENGTH;
}
