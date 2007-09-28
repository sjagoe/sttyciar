#ifndef __PCAPTHREADTICKET_HH__
#define __PCAPTHREADTICKET_HH__

//#include <iostream>

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

#include "alnetworklistener.hh"
#include "lockablequeue.hh"
#include "rawpacket.hh"
#include "interfaceroute.hh"

using boost::shared_ptr;
using boost::weak_ptr;

/*!
A container class for the actual LockableQueue used by the PcapReceiveThread.

The purpose of this class it to hide the complexity of the LockableQueue from
the PcapReceiveThread.

\author Simon Jagoe
*/
class PcapThreadTicket
{
    public:
        /*!
        Construct a PcapThreadTicket with a weak pointer to the NLL.

        This creates the LockableQueue and registers it with the NLL.
        */
        PcapThreadTicket( weak_ptr<ALNetworkListener> nll )
        {
            _networkLogicLayer = nll;
            _receiveBuffer.reset( new LockableQueue<shared_ptr<RawPacket> > );
            _networkLogicLayer.lock()->registerQueue( _receiveBuffer );
        };

        /*!
        Enqueue a packet onto the LockableQueue and notify the NLL that a packet
        has been received.

        \param packet Packet received by the PcapReceiveThread
        */
        void enqueue( const shared_ptr<RawPacket>& packet )
        {
            _receiveBuffer->push( packet );
            _networkLogicLayer.lock()->packetReceived();
        };

    private:
        weak_ptr<ALNetworkListener> _networkLogicLayer; //! Weak pointer to the NLL to notify on packet receipt (weak pointer avoids cyclic dependencies and memory leaks).
        shared_ptr<LockableQueue<shared_ptr<RawPacket> > > _receiveBuffer; //! LockableQueue used by the thread containing this ticket.
};

#endif
