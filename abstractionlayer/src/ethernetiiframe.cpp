#include <ext/algorithm>

#include "ethernetiiframe.hh"
#include "rawpacket.hh"

const int EthernetIIFrame::ETHERNETII_HEAD_LENGTH;
const int EthernetIIFrame::ETHERNETII_MAC_LENGTH;

EthernetIIFrame::EthernetIIFrame( shared_ptr<RawPacket>& packet )
    : DataLinkLayerPacket( packet )
{
    _sourceMAC = (mac_t*) getRawPacket().get();
    _destMAC = (mac_t*) (getRawPacket().get() + ETHERNETII_MAC_LENGTH);
    _etherType = (ethertype_t*) getRawPacket().get() + 2*ETHERNETII_MAC_LENGTH;
}
