#ifndef __IPV4DATAGRAM_HH__
#define __IPV4DATAGRAM_HH__

#include <vector>
#include <boost/array.hpp>

#include "networklayerpacket.hh"

using std::vector;
using boost::array;
using std::pair;

class RawPacket;

class IPv4Datagram: public NetworkLayerPacket
{
    private:
        static const short IPV4_DATAGRAMLENGTH_STORE_LENGTH = 2;
        static const short IPV4_IDENTIFICATION_STORE_LENGTH = 2;
        static const short IPV4_FRAGOFFSET_STORE_LENGTH = 2;
        static const short IPV4_CHECKSUM_STORE_LENGTH = 2;
        static const short IPV4_ADDRESS_STORE_LENGTH = 4;

        static const short IPV4_TEMP_FLAGS_OFFSET_LENGTH = 2;

        static const short IPV4_VERSION_AND_VALUE = 0xF0;
        static const short IPV4_VERSION_SHIFT = 4;

        static const short IPV4_HEADERLENGTH_AND_VALUE = 0x0F;

        static const short IPV4_FLAGS_AND_VALUE = 0xE0;
        static const short IPV4_FLAGS_SHIFT = 5;

        static const short IPV4_OFFSET_AND_VALUE = 0x1F;

        static const unsigned short IPV4_MINIMUM_LENGTH = 20;

        //! IP version (i.e. 4)
        u_char _version;

        //! Length of the header including the options field (excluding data
        //! payload)
        u_char _headerLength;

        //! Type Of Service, specify high throughput etc. Now used for DiffServ
        //! and ECN.
        u_char _typeOfService;

        //! Total length of the datagram including data payload (max 65535,
        //! min 20)
        array<u_char, IPV4_DATAGRAMLENGTH_STORE_LENGTH> _datagramLength;

        //! unique ID of the packet (used in fragmentation and reassembly?)
        array<u_char, IPV4_IDENTIFICATION_STORE_LENGTH> _identification;

        //! 3 bits. 1st is reserved (zero), 2nd is Don't Fragment,
        //! 3rd is More Fragments. (order?)
        u_char _flags;

        //! 13-bit fragment offset field, measured in units of 8-byte blocks.
        array<u_char, IPV4_FRAGOFFSET_STORE_LENGTH> _fragmentationOffset;

        //! Number of hops before the packet is dropped.
        u_char _timeToLive;

        //! The protocol used in the data payload (i.e. TCP, UDP etc)
        u_char _protocol;

        //! Checksum of the header (?) (or datagram ?)
        array<u_char, IPV4_CHECKSUM_STORE_LENGTH> _checksum;

        //! Source IP address
        array<u_char, IPV4_ADDRESS_STORE_LENGTH> _sourceAddress;

        //! Destination IP Address
        array<u_char, IPV4_ADDRESS_STORE_LENGTH> _destinationAddress;

        //! Remainder of the packet - Options and Payload
        vector<u_char> _remainingData;

    public:
        IPv4Datagram() {};
        IPv4Datagram( DataLinkLayerPacket& packet )
        {
            setData( packet );
        };
        void setData( DataLinkLayerPacket& packet );
        RawPacket getRawPacket() const;
//        inline const vector<u_char>& getPayload() const
//        {
//            return _remainingData;
//        };

        const u_char getVersion() const;

        const u_char getHeaderLength() const;

        const u_char getTypeOfService() const;

        const u_int16_t getDatagramLength() const;

        const u_int16_t getIdentification() const;

        const u_char getFlags() const;

        const u_int16_t getFragmentationOffset() const;

        const u_char getTimeToLive() const;

        const u_char getProtocol() const;

        const u_int16_t getChecksum() const;

        const array<u_char, IPV4_ADDRESS_STORE_LENGTH>&
            getSourceAddress() const;

        const array<u_char, IPV4_ADDRESS_STORE_LENGTH>&
            getDestinationAddress() const;
};

#endif
