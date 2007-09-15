#include "nllhub.hh"

#include "interfaceroute.hh"

void NLLHub::routePacket( shared_ptr<RawPacket> packet,
    shared_ptr<InterfaceRoute>& interfaces )
{
    list<shared_ptr<Device> >::const_iterator iter = _devices.begin();

    for (; iter != _devices.end(); iter++)
    {
        if ( interfaces->getSource().get() != iter->get() )
        {
            interfaces->addDestination( *iter );
        }
    }

    getAbstractionLayer()->sendNetworkLayerPacket( packet, interfaces );
}
