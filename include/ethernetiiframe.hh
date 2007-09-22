#ifndef __ETHERNETIIFRAME_HH__
#define __ETHERNETIIFRAME_HH__

//#include <sys/types.h>

#include <boost/shared_array.hpp>
#include <boost/shared_ptr.hpp>

#include "packetaccess.hh"

#include "datalinklayerpacket.hh"

//using std::vector;
using boost::shared_array;
using boost::shared_ptr;

class RawPacket;

typedef struct six_byte mac_t;
typedef struct two_byte ethertype_t;


/*!
EthernetIIFrame encapsulates the Ethernet II Frame header and payload with an
easy to use interface.

This class provides an interface to Ethernet II Frame headers stored in the
encapsulated RawPacket.

\author Simon Jagoe
*/
class EthernetIIFrame: public DataLinkLayerPacket
{
    private:
        static const int ETHERNETII_HEAD_LENGTH = 14; //! Length of an Ethernet II Frame Header
        static const int ETHERNETII_MAC_LENGTH = 6; //! Length of an Ethernet Hardware (MAC) Address

        mac_t* _destMAC; //! A pointer to the part of the packet that contains the destination MAC

        mac_t* _sourceMAC; //! A pointer to the part of the packet that contains the source MAC

        ethertype_t* _etherType; //! A pointer to the part of the packet that contains the EtherType

    public:
        /*!
        Encapsulate the provided RawPacket, and access information contained in
        it.

        \param packet The Packet object containing the raw packet data
        */
        EthernetIIFrame( shared_ptr<RawPacket>& packet );

        /*!
        Set the source MAC in the encapsulated RawPacket to contain the provided
        value.

        \param mac New source MAC address.
        */
        void setSourceMAC( const mac_t& mac );

        /*!
        Set the destination MAC in the encapsulated RawPacket to contain the
        provided value.

        \param mac New destination MAC address.
        */
        void setDestinationMAC( const mac_t& mac );

        /*!
        Set the EtherType in the encapsulated RawPacket to contain the provided
        value.

        \param et New EtherType.
        */
        void setEtherType( const ethertype_t& et );

        /*!
        Return the offset of the frame payload, from the first byte, in number
        or bytes.

        \return Byte offset of the frame payload.
        */
        inline const int getPayloadOffset() const
        {
            return ETHERNETII_HEAD_LENGTH;
        };

        /*!
        Return a reference to the source MAC address.

        \return The source MAC address of the packet.
        */
        const mac_t& getSourceMAC() const;

        /*!
        Return a reference to the destination MAC address.

        \return The destination MAC address of the packet.
        */
        const mac_t& getDestinationMAC() const;

        /*!
        Return a reference to the EtherType of the frame.

        \return The EtherType of the frame.
        */
        const ethertype_t& getEtherType() const;

        // EtherTypes
        static const u_short ETHERTYPE_IPV4 = 0x0800; //! The EtherType of an IPv4 Datagram \see IPv4Datagram
        static const u_short ETHERTYPE_ARP = 0x0806; //! The EtherType of an ARP
};

#endif
