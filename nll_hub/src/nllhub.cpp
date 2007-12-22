#include <iostream>

#include "nllhub.hh"

#include "interfaceroute.hh"

#include "rawpacket.hh"

#include "ethernetiiframe.hh"
#include "ipv4datagram.hh"

void NLLHub::routePacket( shared_ptr<RawPacket>& packet )
{

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


    EthernetIIFrame e( packet );
    IPv4Datagram d( e );
    ip_t ip = d.getSourceAddress();
    std::cout << " - Packet Received from "
        << (int) ip.U_main.S_uchar.b1 << "."
        << (int) ip.U_main.S_uchar.b2 << "."
        << (int) ip.U_main.S_uchar.b3 << "."
        << (int) ip.U_main.S_uchar.b4
        << std::endl;
}
