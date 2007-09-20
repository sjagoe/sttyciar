#include <ext/algorithm>

#include "rawpacket.hh"
#include "interfaceroute.hh"

RawPacket::RawPacket()
{
    _interfaceRoute.reset( new InterfaceRoute() );
}

RawPacket::RawPacket ( const pcap_pkthdr* head, const u_char* packet,
                       const shared_ptr<Device>& sourceDevice )
{
    RawPacket();
    pcap_pkthdr* newHead = new pcap_pkthdr;
    newHead->caplen = head->caplen;
    newHead->len = head->len;

    u_char* newPacket = new u_char[newHead->len];

    __gnu_cxx::copy_n( packet, newHead->len, newPacket );

    _pcapHeader.reset ( newHead );
    _packet.reset ( newPacket );
}

RawPacket::RawPacket ( const shared_ptr<pcap_pkthdr>& head,
                       const shared_array<u_char>& packet,
                       const shared_ptr<Device>& sourceDevice  )
{
    RawPacket();
    _pcapHeader = head;
    _packet = packet;
}

void RawPacket::setPacket ( const pcap_pkthdr* head, const u_char* packet )
{
    _pcapHeader.reset ( ( pcap_pkthdr* ) head );
    _packet.reset ( ( u_char* ) packet );
}

void RawPacket::setPacket ( const u_char* packet, const u_int32_t& length )
{
    initialisePacket( length );
    _packet.reset ( ( u_char* ) packet );
}

void RawPacket::initialisePacket ( const u_int32_t& length )
{
    _packet.reset ( new u_char[length] );
    _pcapHeader.reset ( new pcap_pkthdr );
    _pcapHeader->len = length;
    _pcapHeader->caplen = length;
}

//void RawPacket::insert( const vector<u_char>& data,
//    const bpf_u_int32& from_position, const bpf_u_int32& length,
//    const bpf_u_int32& position )
//{
//    if ( ( data.size() >= (length + from_position) ) &&
//        ( _pcapHeader->len >= (position + length) ) )
//    {
//        vector<u_char>::const_iterator from = data.begin() + from_position;
//        u_char* to = _packet.get() + position;
//        __gnu_cxx::copy_n( from, length, to );
//    }
//}

void RawPacket::addDestination( const shared_ptr<Device>& destinationInterface )
{
    _interfaceRoute->addDestination( destinationInterface );
}
