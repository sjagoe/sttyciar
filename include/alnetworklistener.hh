#ifndef __ALNETWORKLISTENER_HH__
#define __ALNETWORKLISTENER_HH__

#include <QPair>

#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

using boost::scoped_ptr;
using boost::shared_ptr;
using boost::weak_ptr;

class RawPacket;
class InterfaceRoute;
class Device;
//class NLLListener;

#include "abstractionlayer.hh"
#include "lockablequeue.hh"

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
        virtual void packetReceived( shared_ptr<RawPacket>& packet,
            shared_ptr<Device>& device ) = 0;

        virtual void packetReceived() = 0;

        virtual void
        registerQueue( shared_ptr<LockableQueue<QPair<shared_ptr<RawPacket>,
            shared_ptr<InterfaceRoute> > > > ) = 0;

        virtual void exitNow() = 0;
};

#endif
