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



//const u_char IPv4Datagram::getVersion() const
//{
//    return _version;
//}
//
//const u_char IPv4Datagram::getHeaderLength() const
//{
//    return _headerLength;
//}
//
//const u_char IPv4Datagram::getTypeOfService() const
//{
//    return _typeOfService;
//}
//
//const u_int16_t IPv4Datagram::getDatagramLength() const
//{
//    return ( ( _datagramLength[0] << 8 ) |  _datagramLength[1] );
//}
//
//const u_int16_t IPv4Datagram::getIdentification() const
//{
//    return ( ( _identification[0] << 8 ) | _identification[1] );
//}
//
//const u_char IPv4Datagram::getFlags() const
//{
//    return _flags;
//}
//
//const u_int16_t IPv4Datagram::getFragmentationOffset() const
//{
//    return ( ( _fragmentationOffset[0] << 8 ) | _fragmentationOffset[1] );
//}
//
//const u_char IPv4Datagram::getTimeToLive() const
//{
//    return _timeToLive;
//}
//
//const u_char IPv4Datagram::getProtocol() const
//{
//    return _protocol;
//}
//
//const u_int16_t IPv4Datagram::getChecksum() const
//{
//    return ( ( _checksum[0] << 8 ) | _checksum[1] );
//}
//
//const array<u_char, IPv4Datagram::IPV4_ADDRESS_STORE_LENGTH>&
//    IPv4Datagram::getSourceAddress() const
//{
//    return _sourceAddress;
//}
//
//const array<u_char, IPv4Datagram::IPV4_ADDRESS_STORE_LENGTH>&
//    IPv4Datagram::getDestinationAddress() const
//{
//    return _destinationAddress;
//}
