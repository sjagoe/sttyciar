//#include <iostream>
#include <ext/algorithm>

#include "ethernetiiframe.hh"
#include "rawpacket.hh"

const int EthernetIIFrame::ETHERNETII_HEAD_LENGTH;
const int EthernetIIFrame::ETHERNETII_MAC_LENGTH;

EthernetIIFrame::EthernetIIFrame( shared_ptr<RawPacket>& packet )
    : DataLinkLayerPacket( packet )
{
    u_char* temp = getRawPacket()->getPacket().get();

    _destMAC = (mac_t*) temp;
//    std::cout << "memloc" << std::endl;
//    std::cout << (int)_destMAC << std::endl << (int)temp << std::endl
//        << ((void*)_destMAC == (void*)(temp)) << std::endl;

    _sourceMAC = (mac_t*) (temp + ETHERNETII_MAC_LENGTH);
    _etherType = (ethertype_t*)(temp + (2*ETHERNETII_MAC_LENGTH));
}

void EthernetIIFrame::setSourceMAC( const mac_t& mac )
{
    *_sourceMAC = mac;
}

void EthernetIIFrame::setDestinationMAC( const mac_t& mac )
{
    *_destMAC = mac;
}

void EthernetIIFrame::setEtherType( const ethertype_t& et )
{
    *_etherType = et;
}

const mac_t& EthernetIIFrame::getSourceMAC() const
{
    return *_sourceMAC;
};

const mac_t& EthernetIIFrame::getDestinationMAC() const
{
    return *_destMAC;
};

const ethertype_t& EthernetIIFrame::getEtherType() const
{
    return *_etherType;
};
