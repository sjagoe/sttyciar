#ifndef __IPV4DATAGRAM_HH__
#define __IPV4DATAGRAM_HH__

#include <boost/array.hpp>

#include "packet.hh"

#define IPV4_DATAGRAMLENGTH_STORE_LENGTH 2
#define IPV4_IDENTIFICATION_STORE_LENGTH 2
#define IPV4_FRAGOFFSET_STORE_LENGTH 2
#define IPV4_CHECKSUM_STORE_LENGTH 2
#define IPV4_ADDRESS_STORE_LENGTH 4

using boost::array;

class RawPacket;

class IPv4Datagram: public Packet
{
    public:
        IPv4Datagram( RawPacket& packet );
        RawPacket getRawPacket();

    private:
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

};

#endif
