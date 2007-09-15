#ifndef __IPV4DATAGRAM_HH__
#define __IPV4DATAGRAM_HH__

#include <vector>
#include <boost/shared_ptr.hpp>

#include "networklayerpacket.hh"

using std::vector;
using boost::shared_ptr;
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



    public:
        IPv4Datagram( DataLinkLayerPacket& packet )
            : NetworkLayerPacket( packet )
        {

        };

        //void setData( shared_ptr<DataLinkLayerPacket>& packet );

//        inline const vector<u_char>& getPayload() const
//        {
//            return _remainingData;
//        };

//        const u_char getVersion() const;
//
//        const u_char getHeaderLength() const;
//
//        const u_char getTypeOfService() const;
//
//        const u_int16_t getDatagramLength() const;
//
//        const u_int16_t getIdentification() const;
//
//        const u_char getFlags() const;
//
//        const u_int16_t getFragmentationOffset() const;
//
//        const u_char getTimeToLive() const;
//
//        const u_char getProtocol() const;
//
//        const u_int16_t getChecksum() const;
//
//        const array<u_char, IPV4_ADDRESS_STORE_LENGTH>&
//            getSourceAddress() const;
//
//        const array<u_char, IPV4_ADDRESS_STORE_LENGTH>&
//            getDestinationAddress() const;
};

#endif
