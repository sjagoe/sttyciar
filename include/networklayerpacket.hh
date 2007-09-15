#ifndef __NETWORKLAYERPACKET_HH__
#define __NETWORKLAYERPACKET_HH__

#include <boost/shared_ptr.hpp>

#include "packet.hh"
#include "datalinklayerpacket.hh"

using boost::shared_ptr;

class NetworkLayerPacket: public Packet
{
    protected:
        int _networkLayerPacketOffset;

    public:
        NetworkLayerPacket( DataLinkLayerPacket& packet )
        {
            _rawPacket = packet.getRawPacket();
            _networkLayerPacketOffset = packet.getPayloadOffset();
        };

        inline const int& getPacketOffset() const
        {
            return _networkLayerPacketOffset;
        }

        //virtual void setData( DataLinkLayerPacket& packet ) = 0;
        //virtual const vector<u_char>& getPayload() const = 0;
};

#endif
