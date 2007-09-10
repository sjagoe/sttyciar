#ifndef __ALNETWORKLISTENER_HH__
#define __ALNETWORKLISTENER_HH__

#include <boost/shared_ptr.hpp>

using boost::shared_ptr;

class RawPacket;
class InterfaceRoute;
//class NLLListener;

#include "nlllistener.hh"

/*!
The ALNetworkListener class in a (pure virtual) public interface that the
Network Logic Layer modules must implement in order to function with the
Abstraction Layer.

@author Simon Jagoe
*/
class ALNetworkListener
{
    protected:
        shared_ptr<NLLListener> _abstractionLayer;

    public:
        ALNetworkListener() {};
        ALNetworkListener( shared_ptr<NLLListener> abstractionLayer )
        {
            _abstractionLayer = abstractionLayer;
        };
        /*!
        Virtual destructor to allow destructor overriding.
        */
        virtual ~ALNetworkListener() {};

        /*!
        This method is called every time a packet is received by the AL to
        pass the packet data to the NLL for analysis and routing.

        @param packet The raw packet data received from the network.
        @param interfaces An InterfaceRoute object containing the source
        interface, and an empty list of destination interfaces.
        */
        virtual void packetReceived( RawPacket& packet,
            InterfaceRoute& interfaces ) = 0;

        /*!
        register a Network Logic Layer Listener (i.e. the AL) with the NLL
        module.

        @param abstractionLayer the AL that the NLL module must send messages
        to (there is only one AL).
        */
        void registerAL( shared_ptr<NLLListener> abstractionLayer )
        {
            _abstractionLayer = abstractionLayer;
        };
};

#endif
