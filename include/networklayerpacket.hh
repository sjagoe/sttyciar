#ifndef __NETWORKLAYERPACKET_HH__
#define __NETWORKLAYERPACKET_HH__

#include <vector>

#include "packet.hh"
#include "datalinklayerpacket.hh"

using std::vector;

class NetworkLayerPacket: public Packet
{
    public:
        virtual void setData( DataLinkLayerPacket& packet ) = 0;
        //virtual const vector<u_char>& getPayload() const = 0;
};

#endif
