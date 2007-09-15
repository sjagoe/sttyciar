#include "interfaceroute.hh"

InterfaceRoute::InterfaceRoute( shared_ptr<Device>& sourceInterface )
{
    _sourceInterface = sourceInterface;
}

void InterfaceRoute::addDestination( shared_ptr<Device>& destinationInterface )
{
    _destinationInterfaces.push_back( destinationInterface );
}

void InterfaceRoute::clearDestinations()
{
    _destinationInterfaces.clear();
}

//void InterfaceRoute::setDestinations()
//{
//
//}

