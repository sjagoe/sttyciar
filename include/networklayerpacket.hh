#ifndef __NETWORKLAYERPACKET_HH__
#define __NETWORKLAYERPACKET_HH__

#include <boost/shared_ptr.hpp>

#include "packet.hh"
#include "datalinklayerpacket.hh"

using boost::shared_ptr;

/*!
This class inherits basic functionality from Packet and forms a base class for
all Network Layer protocol packets.

\author Simon Jagoe
*/
class NetworkLayerPacket: public Packet
{
    private:
        int _networkLayerPacketOffset; //! The offset of the Network Layer header from the start of the packet.

    protected:
        /*!
        Return the offset of the network layer header.

        \return Offset (in bytes from the start of the packet) of the Network Layer header.
        */
        inline const int& getPacketOffset() const
        {
            return _networkLayerPacketOffset;
        }

    public:
        /*!
        Construct a NetworkLayerPacket from a DataLinkLayerPacket.

        The DataLinkLayerPacket is important so that the Network Layer header
        offset can be extracted.

        This is called from the constructor of subclasses.

        \param packet the DataLinkLayerPacket that contains the
        NetworkLayerPacket.
        */
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
