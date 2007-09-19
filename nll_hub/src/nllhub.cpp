#include "nllhub.hh"

#include "interfaceroute.hh"

#include "rawpacket.hh"

void NLLHub::routePacket( shared_ptr<RawPacket> packet )
{

    list<shared_ptr<Device> >::const_iterator iter = _devices.begin();

    for (; iter != _devices.end(); iter++)
    {
        if ( packet->getInterfaceRoute()->getSource().get() != iter->get() )
        {
            packet->getInterfaceRoute()->addDestination( *iter );
        }
    }

    //getAbstractionLayer()->sendNetworkLayerPacket( packet, interfaces );
}
