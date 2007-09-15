#ifndef __NETWORKLAYERPACKET_HH__
#define __NETWORKLAYERPACKET_HH__

#include <boost/shared_ptr.hpp>

#include "packet.hh"
#include "datalinklayerpacket.hh"

using boost::shared_ptr;

class NetworkLayerPacket: public Packet
{
    private:
        int _networkLayerPacketOffset;

    protected:
        inline const int& getPacketOffset() const
        {
            return _networkLayerPacketOffset;
        }

    public:
        NetworkLayerPacket( DataLinkLayerPacket& packet )
        {
            setRawPacket(packet.getRawPacket());
            _networkLayerPacketOffset = packet.getPayloadOffset();
        };

        // get payload offset?
        // get payload length?

        //virtual void setData( DataLinkLayerPacket& packet ) = 0;
        //virtual const vector<u_char>& getPayload() const = 0;
};

#endif
