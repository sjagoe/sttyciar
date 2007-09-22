#ifndef __LINKLAYERPACKET_HH__
#define __LINKLAYERPACKET_HH__

#include <pcap.h>

#include <boost/shared_array.hpp>
#include <boost/shared_ptr.hpp>

#include "packet.hh"

using boost::shared_array;
using boost::shared_ptr;

class RawPacket;

/*!
This class inherits basic functionality from Packet and forms a base class for
all Data Link Layer protocol packets.

\author Simon Jagoe
*/
class DataLinkLayerPacket: public Packet
{
    public:
        /*!
        Create a DataLinkLayerPacket containing the provided RawPacket.

        This method is called from the constructor of a base class.

        \param packet The RawPacket data that this packet will encapsulate and
        provide access to.
        */
        DataLinkLayerPacket( shared_ptr<RawPacket>& packet )
        {
            setRawPacket( packet );
        };

        /*!
        A virtual destructor to clean up this class.
        */
        virtual ~DataLinkLayerPacket() {};

        //virtual void setData( shared_ptr<RawPacket>& packet ) = 0;

        /*!
        Return the offset of the packet's payload from the start of the packet,
        in number of bytes.

        \return Payload offset in number of bytes.
        */
        virtual const int getPayloadOffset() const = 0;
};

#endif
