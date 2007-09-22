#include <iostream>

#include "nllhub.hh"

#include "interfaceroute.hh"

#include "rawpacket.hh"

#include "ethernetiiframe.hh"
#include "ipv4datagram.hh"

const u_short EthernetIIFrame::ETHERTYPE_ARP;
const u_short EthernetIIFrame::ETHERTYPE_IPV4;

void NLLHub::routePacket( shared_ptr<RawPacket>& packet )
{
    EthernetIIFrame e( packet );
    mac_t dm = e.getDestinationMAC();
    mac_t sm = e.getSourceMAC();
    ethertype_t tt = e.getEtherType();

    printf( "\nDestination MAC: %02X:%02X:%02X:%02X:%02X:%02X\n", dm.b1, dm.b2, dm.b3, dm.b4, dm.b5, dm.b6 );

    printf( "     Source MAC: %02X:%02X:%02X:%02X:%02X:%02X\n", sm.b1, sm.b2, sm.b3, sm.b4, sm.b5, sm.b6 );

    u_short etherType = (tt.U_main.S_uchar.high << 8) + tt.U_main.S_uchar.low;
    printf( "      EtherType: 0x%04X", etherType );
    std::cout << std::endl;
    switch (etherType)
    {
        case EthernetIIFrame::ETHERTYPE_IPV4:
        {
            std::cout << "IP version 4" << std::endl;
            IPv4Datagram d( e );
            ip_t ip = d.getSourceAddress();
            std::cout << " - Packet Received from "
                << (int) ip.U_main.S_uchar.b1 << "."
                << (int) ip.U_main.S_uchar.b2 << "."
                << (int) ip.U_main.S_uchar.b3 << "."
                << (int) ip.U_main.S_uchar.b4
                << std::endl;
            break;
        }
        case EthernetIIFrame::ETHERTYPE_ARP:
        {
            std::cout << " - ARP" << std::endl;
            break;
        }
    }

    shared_ptr<EthernetIIFrame> frame( new EthernetIIFrame( packet ) );

    QList<shared_ptr<Device> >::const_iterator iter = _devices.begin();

    for (; iter != _devices.end(); iter++)
    {
        if ( frame->getRawPacket()->getInterfaceRoute()->getSource().get() != iter->get() )
        {
            frame->getRawPacket()->getInterfaceRoute()->addDestination( *iter );
        }
    }

    getAbstractionLayer()->sendDataLinkLayerPacket( frame );
}
