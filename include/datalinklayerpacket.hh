#ifndef __LINKLAYERPACKET_HH__
#define __LINKLAYERPACKET_HH__

#include <pcap.h>

#include <boost/shared_array.hpp>
#include <boost/shared_ptr.hpp>

#include "packet.hh"

using boost::shared_array;
using boost::shared_ptr;

class RawPacket;

class DataLinkLayerPacket: public Packet
{
    public:
        DataLinkLayerPacket( shared_ptr<RawPacket>& packet )
        {
            setRawPacket( packet );
        };

        virtual ~DataLinkLayerPacket() {};

        //virtual void setData( shared_ptr<RawPacket>& packet ) = 0;
        virtual const int getPayloadOffset() const = 0;
};

#endif
