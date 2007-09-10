#ifndef __ALNETWORKLISTENER_HH__
#define __ALNETWORKLISTENER_HH__

class RawPacket;
class InterfaceRoute;

/*!
The ALNetworkListener class in a (pure virtual) public interface that the
Network Logic Layer modules must implement in order to function with the
Abstraction Layer.

@author Simon Jagoe
*/
class ALNetworkListener
{
    public:
        /*!
        This method is called every time a packet is received by the AL to
        pass the packet data to the NLL for analysis and routing.

        @param packet The raw packet data received from the network.
        @param interfaces An InterfaceRoute object containing the source
        interface, and an empty list of destination interfaces.
        */
        virtual void packetReceived( RawPacket& packet,
            InterfaceRoute& interfaces ) = 0;
};

#endif
