#ifndef __IPV4DATAGRAM_HH__
#define __IPV4DATAGRAM_HH__

#include <vector>
#include <boost/shared_ptr.hpp>

#include "packetaccess.hh"

#include "networklayerpacket.hh"

typedef struct four_byte ip_t;
typedef struct two_byte two_byte;

using std::vector;
using boost::shared_ptr;
using std::pair;

class RawPacket;

class IPv4Datagram: public NetworkLayerPacket
{
    private:
        static const short IPV4_TYPEOFSERVICE_OFFSET = 1;
        static const short IPV4_HEADERLENGTH_OFFSET = 2;
        static const short IPV4_IDENTIFICATION_OFFSET = 4;
        static const short IPV4_FLAGS_FRAG_OFFSET = 6;
        static const short IPV4_TIMETOLIVE_OFFSET = 8;
        static const short IPV4_PROTOCOL_OFFSET = 9;
        static const short IPV4_CHECKSUM_OFFSET = 10;
        static const short IPV4_SOURCEADDRESS_OFFSET = 12;
        static const short IPV4_DESTINATIONADDRESS_OFFSET = 16;

//        static const short IPV4_DATAGRAMLENGTH_STORE_LENGTH = 2;
//        static const short IPV4_IDENTIFICATION_STORE_LENGTH = 2;
//        static const short IPV4_FRAGOFFSET_STORE_LENGTH = 2;
//        static const short IPV4_CHECKSUM_STORE_LENGTH = 2;
//        static const short IPV4_ADDRESS_STORE_LENGTH = 4;
//
//        static const short IPV4_TEMP_FLAGS_OFFSET_LENGTH = 2;

        static const short IPV4_VERSION_AND_VALUE = 0xF0;
        static const short IPV4_VERSION_SHIFT = 4;

        static const short IPV4_HEADERLENGTH_AND_VALUE = 0x0F;

        static const short IPV4_FLAGS_AND_VALUE = 0xE0;
        static const short IPV4_FLAGS_SHIFT = 5;

        static const short IPV4_OFFSET_AND_VALUE = 0x1F;

        static const unsigned short IPV4_MINIMUM_LENGTH = 20;

        u_char _version;
        u_char _headerLength;

        u_char* _typeOfService;

        two_byte* _totalLength;

        two_byte* _identification;

        u_char _flags;

        two_byte _fragmentationOffset;

        u_char* _timeToLive;

        u_char* _protocol;

        two_byte* _checksum;

        ip_t* _sourceIP;

        ip_t* _destinationIP;

        u_char* _options;

        int _payloadOffset;

    public:
        IPv4Datagram( DataLinkLayerPacket& packet );

        const u_char& getVersion() const;

        const u_char& getHeaderLength() const;

        const u_char& getTypeOfService() const;

        const two_byte& getDatagramLength() const;

        const two_byte& getIdentification() const;

        const u_char& getFlags() const;

        const two_byte& getFragmentationOffset() const;

        const u_char& getTimeToLive() const;

        const u_char& getProtocol() const;

        const two_byte& getChecksum() const;

        const ip_t& getSourceAddress() const;

        const ip_t& getDestinationAddress() const;
};

#endif
