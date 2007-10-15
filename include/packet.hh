#ifndef __PACKET_HH__
#define __PACKET_HH__

#include <boost/shared_ptr.hpp>

using boost::shared_ptr;

//class RawPacket;
#include "rawpacket.hh"
class Device;


/*!
The Packet Class forms a base class for all packet types.

This class is inherited by classes such as the DataLinkLayerPacket and
NetworkLayerPacket, which are inherited by classes forming the packet structure
for specific protocols

\author Simon Jagoe
*/
class Packet
{
    private:
        //! A pointer to the RawPacket containing the actual packet data
        shared_ptr<RawPacket> _rawPacket;

    protected:
        /*!
        Set the pointer to the raw packet data.

        \param rawPacket A Boost::shared_ptr to the RawPacket
        **/
        void setRawPacket( const shared_ptr<RawPacket>& rawPacket )
        {
            _rawPacket = rawPacket;
        };

    public:
        /*!
        Virtual destructor, resetting the boost::shared_ptr.
        */
        virtual ~Packet()
        {
            _rawPacket.reset();
        };

        /*!
        Return a const reference to the RawPacket shared_ptr.
        */
        const shared_ptr<RawPacket>& getRawPacket() const
        {
            return _rawPacket;
        };

        /*!
        Add a destination to the routing information contained in the RawPacket.

        \param destinationInterface A shared_ptr to the destination Device
        (interface).
        */
        void addDestination( const shared_ptr<Device>& destinationInterface )
        {
            _rawPacket->addDestination( destinationInterface );
        }

};

#endif
