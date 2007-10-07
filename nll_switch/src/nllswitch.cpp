#include "nllswitch.hh"

#include "interfaceroute.hh"

#include "rawpacket.hh"

#include "ethernetiiframe.hh"

void NLLSwitch::update( int millisecondsElapsed )
{
    this->_lookupTable.updateTime( millisecondsElapsed );
}

void NLLSwitch::routePacket( shared_ptr<RawPacket>& packet )
{
    shared_ptr<EthernetIIFrame> frame( new EthernetIIFrame(packet) );

    mac_t source = frame->getSourceMAC();
    mac_t destination = frame->getDestinationMAC();

    shared_ptr<Device> sourceDevice = frame->getRawPacket()->getInterfaceRoute()->getSource();
    this->_lookupTable.addEntry( source, sourceDevice );

    shared_ptr<Device> destinationDevice = this->_lookupTable.lookupEntry( destination );

//    if (( destinationDevice.get() != 0 ) && ( sourceDevice.get() != destinationDevice.get() ))
    if ( destinationDevice.get() != 0 )
    {
        frame->getRawPacket()->getInterfaceRoute()->addDestination( destinationDevice );
    }
//    else if ( destinationDevice.get() == 0 )
    else
    {
        QList<shared_ptr<Device> >::const_iterator iter = _devices.begin();

        for (; iter != _devices.end(); iter++)
        {
            if ( frame->getRawPacket()->getInterfaceRoute()->getSource().get() != iter->get() )
            {
                frame->getRawPacket()->getInterfaceRoute()->addDestination( *iter );
            }
        }
    }
    getAbstractionLayer()->sendDataLinkLayerPacket( frame );
}
