#ifndef __IPV4DATAGRAM_HH__
#define __IPV4DATAGRAM_HH__

//#include <vector>
#include <boost/shared_ptr.hpp>

#include "packetaccess.hh"

#include "networklayerpacket.hh"

typedef struct four_byte ip_t;
typedef struct two_byte two_byte;

//using std::vector;
using boost::shared_ptr;
using std::pair;

class RawPacket;

/*!
IPv4Datagram encapsulates the IP version 4 Datagram header and payload with an
easy to use interface.

This class provides an interface to IP version 4 Datagram headers stored in the
encapsulated RawPacket.

\author Simon Jagoe
*/
class IPv4Datagram: public NetworkLayerPacket
{
    private:
        static const short IPV4_TYPEOFSERVICE_OFFSET = 1; //! TOS field offset from the start of the IPv4 Header
        static const short IPV4_HEADERLENGTH_OFFSET = 2; //! Header Length field offset from the start of the IPv4 Header
        static const short IPV4_IDENTIFICATION_OFFSET = 4; //! ID field offset from the start of the IPv4 Header
        static const short IPV4_FLAGS_FRAG_OFFSET = 6; //! (Flags & Fragment Offset) field offset from the start of the IPv4 Header
        static const short IPV4_TIMETOLIVE_OFFSET = 8; //! TTL field offset from the start of the IPv4 Header
        static const short IPV4_PROTOCOL_OFFSET = 9; //! Protocol field offset from the start of the IPv4 Header
        static const short IPV4_CHECKSUM_OFFSET = 10; //! Header Checksum field offset from the start of the IPv4 Header
        static const short IPV4_SOURCEADDRESS_OFFSET = 12; //! Source IP field offset from the start of the IPv4 Header
        static const short IPV4_DESTINATIONADDRESS_OFFSET = 16; //! Destination IP field offset from the start of the IPv4 Header

        static const short IPV4_VERSION_AND_VALUE = 0xF0; //! Logical AND value to extract the Version from the first Byte
        static const short IPV4_VERSION_SHIFT = 4; //! Logical shift amount to extract the Version from the first Byte

        static const short IPV4_HEADERLENGTH_AND_VALUE = 0x0F; //! Logical AND value to extract the Header Length from the first Byte

        static const short IPV4_FLAGS_AND_VALUE = 0xE0; //! Logical AND value to extract the Flags from the Flags & Frag Offset bytes
        static const short IPV4_FLAGS_SHIFT = 5; //! Logical shift amount to extract the Flags from the Flags & Frag Offset bytes

        static const short IPV4_OFFSET_AND_VALUE = 0x1F; //! Logical AND value to extract the Fragmentation Offset from the Flags & Frag Offset bytes

        static const unsigned short IPV4_MINIMUM_LENGTH = 20; //! The minimum size in bytes of an IPv4 header.

        u_char _version; //! The version field of the header
        u_char _headerLength; //! The length (in 32-bit words) of the header

        u_char* _typeOfService; //! Access to the Type Of Service field

        two_byte* _totalLength; //! Access to the Total Length field

        two_byte* _identification; //! Access to the ID Field

        u_char _flags; //! The Flags field

        two_byte _fragmentationOffset; //! The Fragmentation offset

        u_char* _timeToLive; //! Access to the TTL field

        u_char* _protocol; //! Access to the Protocol field

        two_byte* _checksum; //! Access to the Checksum Field

        ip_t* _sourceIP; //! Access to the Source IP

        ip_t* _destinationIP; //! Access to the Destination IP

        u_char* _options; //! Access to the Options field

        int _payloadOffset; //! Offset of the payload in Bytes

    public:
        /*!
        Construct an IPv4 datagram from a specific DataLinkLayerPacket.
        This takes a DLL packet because it needs to extract the DLL packet
        payload offset.

        \param packet DataLinkLayerPacket to extract IPv4 header information from
        */
        IPv4Datagram( DataLinkLayerPacket& packet );

        /*!
        Return the IP version...

        \return Version field of the IP header.
        */
        const u_char& getVersion() const;

        /*!
        Return the IP header length.

        \return Header Length field of the IP header.
        */
        const u_char& getHeaderLength() const;

        /*!
        Return the Type of Service

        \return Type of Service field of the IP header.
        */
        const u_char& getTypeOfService() const;

        /*!
        Return the Datagram Length

        \return Total Length field of the IP header.
        */
        const two_byte& getDatagramLength() const;

        /*!
        Return the Identification field

        \return Identification field of the IP header.
        */
        const two_byte& getIdentification() const;

        /*!
        Return the Flags

        \return Flags field of the IP header.
        */
        const u_char& getFlags() const;

        /*!
        Return the Fragmentation Offset

        \return Fragmentation Offset field of the IP header.
        */
        const two_byte& getFragmentationOffset() const;

        /*!
        Return the Time To Live

        \return Time To Live field of the IP header.
        */
        const u_char& getTimeToLive() const;

        /*!
        Return the Transport Layer protocol ID

        \return Protocol field of the IP header.
        */
        const u_char& getProtocol() const;

        /*!
        Return the Checksum

        \return Checksum field of the IP header.
        */
        const two_byte& getChecksum() const;

        /*!
        Return the Source IP Address

        \return Source Address field of the IP header.
        */
        const ip_t& getSourceAddress() const;

        /*!
        Return the Destination IP Address

        \return Destination Address field of the IP header.
        */
        const ip_t& getDestinationAddress() const;
};

#endif
