#ifndef __PCAPTHREADTICKET_HH__
#define __PCAPTHREADTICKET_HH__

#include <QPair>

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

#include "alnetworklistener.hh"
#include "lockablequeue.hh"
#include "rawpacket.hh"
#include "interfaceroute.hh"

using boost::shared_ptr;
using boost::weak_ptr;

class PcapThreadTicket
{
    public:
        PcapThreadTicket( weak_ptr<ALNetworkListener> nll )
        {
            _networkLogicLayer = nll;
            _receiveBuffer.reset( new LockableQueue<QPair<shared_ptr<RawPacket>,
                shared_ptr<InterfaceRoute> > > );
            _networkLogicLayer.lock()->registerQueue( _receiveBuffer );
        };

        void enqueue( shared_ptr<RawPacket> packet,
            shared_ptr<Device> device )
        {
            shared_ptr<InterfaceRoute>
                interfaces( new InterfaceRoute( device ) );
            _receiveBuffer->push( qMakePair( packet, interfaces ) );
            _networkLogicLayer.lock()->packetReceived();
        };

    private:
        weak_ptr<ALNetworkListener> _networkLogicLayer;
        shared_ptr<LockableQueue<QPair<shared_ptr<RawPacket>,
            shared_ptr<InterfaceRoute> > > > _receiveBuffer;
};

#endif
