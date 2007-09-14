#include "interfaceroute.hh"

InterfaceRoute::InterfaceRoute( string& sourceInterface )
{
    _sourceInterface = sourceInterface;
}

void InterfaceRoute::addDestination( string& destinationInterface )
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

const vector<string>& InterfaceRoute::getDestinations() const
{
    return _destinationInterfaces;
}

const string& InterfaceRoute::getSource() const
{
    return _sourceInterface;
}
