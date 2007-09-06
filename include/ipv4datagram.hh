#ifndef __IPV4DATAGRAM_HH__
#define __IPV4DATAGRAM_HH__

#include <boost/array.hpp>

#define IPV4_DATAGRAMLENGTH_STORE_LENGTH 2
#define IPV4_IDENTIFICATION_STORE_LENGTH 2
#define IPV4_FRAGOFFSET_STORE_LENGTH 2
#define IPV4_CHECKSUM_STORE_LENGTH 2
#define IPV4_ADDRESS_STORE_LENGTH 4

using boost::array;

class RawPacket;

class IPv4Datagram
{
    public:
        IPv4Datagram( RawPacket& packet );

    private:
        u_char version; //! IP version (i.e. 4)
        u_char headerLength; //! Length of the header including the options field (excluding data payload)
        u_char typeOfService; //! Type Of Service, specify high throughput etc. Now used for DiffServ and ECN.
        array<u_char, IPV4_DATAGRAMLENGTH_STORE_LENGTH> datagramLength; //! Total length of the datagram including data payload (max 65535, min 20)
        array<u_char, IPV4_IDENTIFICATION_STORE_LENGTH> identification; //! unique ID of the packet (used in fragmentation and reassembly?)
        u_char flags; //! 3 bits. 1st is reserved (zero), 2nd is Don't Fragment, 3rd is More Fragments. (order?)
        array<u_char, IPV4_FRAGOFFSET_STORE_LENGTH> fragmentationOffset; //! 13-bit fragment offset field, measured in units of 8-byte blocks.
        u_char timeToLive; //! Number of hops before the packet is dropped.
        u_char protocol; //! The protocol used in the data payload (i.e. TCP, UDP etc)
        array<u_char, IPV4_CHECKSUM_STORE_LENGTH> checksum; //! Checksum of the header (?) (or datagram ?)
        array<u_char, IPV4_ADDRESS_STORE_LENGTH> sourceAddress; //! Source IP address
        array<u_char, IPV4_ADDRESS_STORE_LENGTH> destinationAddress; //! Destination IP Address
};

#endif
