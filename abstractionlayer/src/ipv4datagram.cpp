#include <ext/algorithm>
#include <algorithm>

#include "ipv4datagram.hh"

#include "rawpacket.hh"

#include "ethernetiiframe.hh"

const short IPv4Datagram::IPV4_DATAGRAMLENGTH_STORE_LENGTH;
const short IPv4Datagram::IPV4_IDENTIFICATION_STORE_LENGTH;
const short IPv4Datagram::IPV4_FRAGOFFSET_STORE_LENGTH;
const short IPv4Datagram::IPV4_CHECKSUM_STORE_LENGTH;
const short IPv4Datagram::IPV4_ADDRESS_STORE_LENGTH;

const short IPv4Datagram::IPV4_TEMP_FLAGS_OFFSET_LENGTH;

const short IPv4Datagram::IPV4_VERSION_AND_VALUE;
const short IPv4Datagram::IPV4_VERSION_SHIFT;

const short IPv4Datagram::IPV4_HEADERLENGTH_AND_VALUE;

const short IPv4Datagram::IPV4_FLAGS_AND_VALUE;
const short IPv4Datagram::IPV4_FLAGS_SHIFT;

const short IPv4Datagram::IPV4_OFFSET_AND_VALUE;

const unsigned short IPv4Datagram::IPV4_MINIMUM_LENGTH;

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
            IPV4_VERSION_SHIFT;

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

        iter = out.first;

        // flags_offset_bytes
        array<u_char, IPV4_TEMP_FLAGS_OFFSET_LENGTH> flags_offset_bytes;
        out = __gnu_cxx::copy_n( iter, IPV4_TEMP_FLAGS_OFFSET_LENGTH,
            flags_offset_bytes.begin() );

        // _flags
        _flags = ( flags_offset_bytes[0] & IPV4_FLAGS_AND_VALUE ) >>
            IPV4_FLAGS_SHIFT;

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

        iter = out1.first;

        // _destinationAddress
        out1 = __gnu_cxx::copy_n( iter, IPV4_ADDRESS_STORE_LENGTH,
            _destinationAddress.begin() );

        iter = out1.first;

        // _remainingData
        unsigned int length = ( _datagramLength[0] << 8 ) | _datagramLength[1];
        if ( length > IPV4_MINIMUM_LENGTH)
        {

            if (( length > data.size() )
                && ( data.size() > IPV4_MINIMUM_LENGTH ) )
            {
                //std::copy( iter, data.end(), _remainingData.begin() );
                _remainingData.resize( data.size() - IPV4_MINIMUM_LENGTH );
                __gnu_cxx::copy_n( iter, ( data.size() - IPV4_MINIMUM_LENGTH ),
                    _remainingData.begin() );
            }
            else if ( length >= data.size() )
            {
                _remainingData.resize( length - IPV4_MINIMUM_LENGTH );
                __gnu_cxx::copy_n( iter, ( length - IPV4_MINIMUM_LENGTH ),
                    _remainingData.begin() );
            }
        }
    }
}

RawPacket IPv4Datagram::getRawPacket() const
{
    RawPacket raw;

    raw.append( (_version << IPV4_VERSION_SHIFT) | _headerLength );

    raw.append( _typeOfService );

    raw.append( _datagramLength[0] );
    raw.append( _datagramLength[1] );

    raw.append( _identification[0] );
    raw.append( _identification[1] );

    raw.append( ( _flags << IPV4_FLAGS_SHIFT ) | _fragmentationOffset[0] );
    raw.append( _fragmentationOffset[1] );

    raw.append( _timeToLive );

    raw.append( _protocol );

    raw.append( _checksum[0] );
    raw.append( _checksum[1] );

    raw.append( _sourceAddress[0] );
    raw.append( _sourceAddress[1] );
    raw.append( _sourceAddress[2] );
    raw.append( _sourceAddress[3] );

    raw.append( _destinationAddress[0] );
    raw.append( _destinationAddress[1] );
    raw.append( _destinationAddress[2] );
    raw.append( _destinationAddress[3] );

//    vector<u_char>::const_iterator iter = _remainingData.begin();
//    for (; iter != _remainingData.end(); iter++)
//    {
//        raw.append( *iter );
//    }

    raw.append( _remainingData );

    return raw;
}

const u_char IPv4Datagram::getVersion() const
{
    return _version;
}

const u_char IPv4Datagram::getHeaderLength() const
{
    return _headerLength;
}

const u_char IPv4Datagram::getTypeOfService() const
{
    return _typeOfService;
}

const u_int16_t IPv4Datagram::getDatagramLength() const
{
    return ( ( _datagramLength[0] << 8 ) |  _datagramLength[1] );
}

const u_int16_t IPv4Datagram::getIdentification() const
{
    return ( ( _identification[0] << 8 ) | _identification[1] );
}

const u_char IPv4Datagram::getFlags() const
{
    return _flags;
}

const u_int16_t IPv4Datagram::getFragmentationOffset() const
{
    return ( ( _fragmentationOffset[0] << 8 ) | _fragmentationOffset[1] );
}

const u_char IPv4Datagram::getTimeToLive() const
{
    return _timeToLive;
}

const u_char IPv4Datagram::getProtocol() const
{
    return _protocol;
}

const u_int16_t IPv4Datagram::getChecksum() const
{
    return ( ( _checksum[0] << 8 ) | _checksum[1] );
}

const array<u_char, IPv4Datagram::IPV4_ADDRESS_STORE_LENGTH>&
    IPv4Datagram::getSourceAddress() const
{
    return _sourceAddress;
}

const array<u_char, IPv4Datagram::IPV4_ADDRESS_STORE_LENGTH>&
    IPv4Datagram::getDestinationAddress() const
{
    return _destinationAddress;
}
