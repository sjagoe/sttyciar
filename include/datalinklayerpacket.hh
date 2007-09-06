#ifndef __LINKLAYERPACKET_HH__
#define __LINKLAYERPACKET_HH__

#include <vector>

#include "packet.hh"

using std::vector;

class RawPacket;

class DataLinkLayerPacket: public Packet
{
    public:
        virtual void setData( RawPacket& packet ) = 0;
        virtual const vector<u_char>& getPayload() const = 0;
};

#endif
