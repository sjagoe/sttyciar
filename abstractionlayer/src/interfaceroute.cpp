#include "interfaceroute.hh"

InterfaceRoute::InterfaceRoute()
{
    _destinationInterfaces.reset( new QList<shared_ptr<Device> > );
}

InterfaceRoute::InterfaceRoute( const shared_ptr<Device>& sourceInterface )
{
    InterfaceRoute();
    setSource( sourceInterface );
}

void InterfaceRoute::setSource( const shared_ptr<Device>& sourceInterface )
{
    _sourceInterface = sourceInterface;
}

void InterfaceRoute::addDestination( const shared_ptr<Device>& destinationInterface )
{
    _destinationInterfaces->push_back( destinationInterface );
}

void InterfaceRoute::clearDestinations()
{
    _destinationInterfaces->clear();
}
