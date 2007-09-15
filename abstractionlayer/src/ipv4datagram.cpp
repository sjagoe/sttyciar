#include <iostream>
#include <ext/algorithm>
#include <algorithm>

#include "ipv4datagram.hh"

#include "rawpacket.hh"

#include "ethernetiiframe.hh"

using std::cout;
using std::endl;

const short IPv4Datagram::IPV4_TYPEOFSERVICE_OFFSET;
const short IPv4Datagram::IPV4_HEADERLENGTH_OFFSET;
const short IPv4Datagram::IPV4_IDENTIFICATION_OFFSET;
const short IPv4Datagram::IPV4_FLAGS_FRAG_OFFSET;
const short IPv4Datagram::IPV4_TIMETOLIVE_OFFSET;
const short IPv4Datagram::IPV4_PROTOCOL_OFFSET;
const short IPv4Datagram::IPV4_CHECKSUM_OFFSET;
const short IPv4Datagram::IPV4_SOURCEADDRESS_OFFSET;
const short IPv4Datagram::IPV4_DESTINATIONADDRESS_OFFSET;

const short IPv4Datagram::IPV4_VERSION_AND_VALUE;
const short IPv4Datagram::IPV4_VERSION_SHIFT;

const short IPv4Datagram::IPV4_HEADERLENGTH_AND_VALUE;

const short IPv4Datagram::IPV4_FLAGS_AND_VALUE;
const short IPv4Datagram::IPV4_FLAGS_SHIFT;

const short IPv4Datagram::IPV4_OFFSET_AND_VALUE;

const unsigned short IPv4Datagram::IPV4_MINIMUM_LENGTH;

IPv4Datagram::IPv4Datagram ( DataLinkLayerPacket& packet )
        : NetworkLayerPacket ( packet )
{
    u_char* temp = getRawPacket()->getPacket().get() + getPacketOffset();

    _version = ( ( *temp ) & IPV4_VERSION_AND_VALUE ) >> IPV4_VERSION_SHIFT;

    _headerLength = ( ( *temp ) & IPV4_HEADERLENGTH_AND_VALUE );

    _typeOfService = ( temp + IPV4_TYPEOFSERVICE_OFFSET );

    _totalLength = ( two_byte* ) ( temp + IPV4_HEADERLENGTH_OFFSET );

    _identification = ( two_byte* ) ( temp + IPV4_IDENTIFICATION_OFFSET );

    _flags = ( ( * ( temp + IPV4_FLAGS_FRAG_OFFSET ) ) & IPV4_FLAGS_AND_VALUE )
             >> IPV4_FLAGS_SHIFT;

    two_byte* temp_two = ( two_byte* ) ( temp + IPV4_FLAGS_FRAG_OFFSET );

    _fragmentationOffset = *temp_two;
    _fragmentationOffset.U_main.S_uchar.high &= IPV4_OFFSET_AND_VALUE;
    temp_two = 0;

    _timeToLive = temp + IPV4_TIMETOLIVE_OFFSET;

    _protocol = temp + IPV4_PROTOCOL_OFFSET;

    _checksum = ( two_byte* ) ( temp + IPV4_CHECKSUM_OFFSET );

    _sourceIP = ( ip_t* ) ( temp + IPV4_SOURCEADDRESS_OFFSET );

    _destinationIP = ( ip_t* ) ( temp + IPV4_DESTINATIONADDRESS_OFFSET );

    _payloadOffset = ( ( int ) _headerLength ) * 4;

    if ( _payloadOffset > IPV4_MINIMUM_LENGTH )
    {
        _options = temp + IPV4_MINIMUM_LENGTH;
    }
    else
    {
        _options = 0;
    }
};

const u_char& IPv4Datagram::getVersion() const
{
    return _version;
}

const u_char& IPv4Datagram::getHeaderLength() const
{
    return _headerLength;
}

const u_char& IPv4Datagram::getTypeOfService() const
{
    return *_typeOfService;
}

const two_byte& IPv4Datagram::getDatagramLength() const
{
    return *_totalLength;
}

const two_byte& IPv4Datagram::getIdentification() const
{
    return *_identification;
}

const u_char& IPv4Datagram::getFlags() const
{
    return _flags;
}

const two_byte& IPv4Datagram::getFragmentationOffset() const
{
    return _fragmentationOffset;
}

const u_char& IPv4Datagram::getTimeToLive() const
{
    return *_timeToLive;
}

const u_char& IPv4Datagram::getProtocol() const
{
    return *_protocol;
}

const two_byte& IPv4Datagram::getChecksum() const
{
    return *_checksum;
}

const ip_t& IPv4Datagram::getSourceAddress() const
{
    return *_sourceIP;
}

const ip_t& IPv4Datagram::getDestinationAddress() const
{
    return *_destinationIP;
}
