#ifndef __ALNETWORKLISTENER_HH__
#define __ALNETWORKLISTENER_HH__

class RawPacket;
class InterfaceRoute;

class ALNetworkListener
{
    public:
        virtual void packetReceived( RawPacket& packet,
            InterfaceRoute& interfaces ) = 0;
};

#endif
