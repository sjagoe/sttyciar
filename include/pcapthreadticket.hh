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

class PcapThreadTicket
{
    public:
        PcapThreadTicket( weak_ptr<ALNetworkListener> nll )
        {
            _networkLogicLayer = nll;
            _receiveBuffer.reset( new LockableQueue<shared_ptr<RawPacket> > );
            _networkLogicLayer.lock()->registerQueue( _receiveBuffer );
        };

        void enqueue( const shared_ptr<RawPacket>& packet )
        {
            _receiveBuffer->push( packet );
//            if (packet.get() == 0)
//                std::cout << "Null pointer in PcapThreadTicket::enqueue()" << std::endl;
//            else
//                std::cout << "Non-Null pointer in PcapThreadTicket::enqueue()" << std::endl;
            _networkLogicLayer.lock()->packetReceived();
        };

    private:
        weak_ptr<ALNetworkListener> _networkLogicLayer;
//        shared_ptr<LockableQueue<QPair<shared_ptr<RawPacket>,
//            shared_ptr<InterfaceRoute> > > > _receiveBuffer;
        shared_ptr<LockableQueue<shared_ptr<RawPacket> > > _receiveBuffer;
};

#endif
