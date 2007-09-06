#include <ext/algorithm>

#include "ipv4datagram.hh"

#include "rawpacket.hh"

#include "ethernetiiframe.hh"

//#define IPV4_DATAGRAMLENGTH_STORE_LENGTH 2
//#define IPV4_IDENTIFICATION_STORE_LENGTH 2
//#define IPV4_FRAGOFFSET_STORE_LENGTH 2
//#define IPV4_CHECKSUM_STORE_LENGTH 2
//#define IPV4_ADDRESS_STORE_LENGTH 4
//
//#define IPV4_TEMP_FLAGS_OFFSET_LENGTH 2
//
//#define IPV4_VERSION_AND_VALUE 0xF0
//#define IPV4_VERSION_LEFT_SHIFT 4
//
//#define IPV4_HEADERLENGTH_AND_VALUE 0x0F
//
//#define IPV4_FLAGS_AND_VALUE 0xE0
//#define IPV4_FLAGS_LEFT_SHIFT 13
//
//#define IPV4_OFFSET_AND_VALUE 0x1F
//
//#define IPV4_MINIMUM_LENGTH 20

//IPv4Datagram::IPv4Datagram( RawPacket& packet )
//IPv4Datagram::IPv4Datagram( EthernetIIFrame& frame )
void IPv4Datagram::setData( DataLinkLayerPacket& packet )
{
    // get the raw packet vector
    vector<u_char> data = packet.getPayload();

    // make sure the IP header is at least the minimum length
    if ( data.size() >= IPV4_MINIMUM_LENGTH )
    {
        // get an iterator to the start
        vector<u_char>::const_iterator iter = data.begin();

        // version and header length byte
        u_char ver_headlength_byte = *iter;

        iter++;

        // extract the version field from the byte
        _version = ( ver_headlength_byte & IPV4_VERSION_AND_VALUE ) >>
            IPV4_VERSION_LEFT_SHIFT;

        // extract the header length field from the byte
        _headerLength = ( ver_headlength_byte & IPV4_HEADERLENGTH_AND_VALUE );

        // type of service byte
        _typeOfService = *iter;

        iter++;

        // _datagramLength
        pair<vector<u_char>::const_iterator,
            array<u_char, IPV4_DATAGRAMLENGTH_STORE_LENGTH>::const_iterator >
            out = __gnu_cxx::copy_n( iter, IPV4_DATAGRAMLENGTH_STORE_LENGTH,
            _datagramLength.begin() );

        iter = out.first;

        // _identification
        out = __gnu_cxx::copy_n( iter, IPV4_IDENTIFICATION_STORE_LENGTH,
            _identification.begin() );

        // flags_offset_bytes
        array<u_char, IPV4_TEMP_FLAGS_OFFSET_LENGTH> flags_offset_bytes;
        out = __gnu_cxx::copy_n( iter, IPV4_TEMP_FLAGS_OFFSET_LENGTH,
            flags_offset_bytes.begin() );

        // _flags
        _flags = ( flags_offset_bytes[0] & IPV4_FLAGS_AND_VALUE ) >>
            IPV4_FLAGS_LEFT_SHIFT;

        // _fragmentationOffset
        _fragmentationOffset = flags_offset_bytes;
        _fragmentationOffset[0] = ( _fragmentationOffset[0] &
            IPV4_OFFSET_AND_VALUE);

        iter = out.first;

        // _timeToLive
        _timeToLive = *iter;

        iter++;

        // _protocol
        _protocol = *iter;

        iter++;

        // _checksum
        out = __gnu_cxx::copy_n( iter, IPV4_CHECKSUM_STORE_LENGTH,
            _checksum.begin() );

        iter = out.first;

        // _sourceAddress
        pair<vector<u_char>::const_iterator, array<u_char,
            IPV4_ADDRESS_STORE_LENGTH>::const_iterator>
            out1 = __gnu_cxx::copy_n( iter, IPV4_ADDRESS_STORE_LENGTH,
            _sourceAddress.begin() );

        // _destinationAddress
        out1 = __gnu_cxx::copy_n( iter, IPV4_ADDRESS_STORE_LENGTH,
            _destinationAddress.begin() );

        iter = out1.first;

        // _remainingData
        _easyLength = ( _datagramLength[0] << 8 ) & _datagramLength[1];
        if (_easyLength > IPV4_MINIMUM_LENGTH)
        {
            _remainingData.resize( _easyLength - IPV4_MINIMUM_LENGTH );
            __gnu_cxx::copy_n( iter, ( _easyLength - IPV4_MINIMUM_LENGTH ),
                _remainingData.begin() );
        }
    }
}

RawPacket IPv4Datagram::getRawPacket()
{
    RawPacket raw;

    return raw;
}
