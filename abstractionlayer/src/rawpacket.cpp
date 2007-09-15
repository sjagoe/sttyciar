//#include <algorithm>
#include <ext/algorithm>

#include "rawpacket.hh"

RawPacket::RawPacket()
{
    _packet.reset();
    _pcapHeader.reset();
}

RawPacket::RawPacket ( const pcap_pkthdr* head, const u_char* packet )
{
    _pcapHeader.reset ( ( pcap_pkthdr* ) head );
    _packet.reset ( ( u_char* ) packet );
}

RawPacket::RawPacket ( const shared_ptr<pcap_pkthdr>& head,
                       const shared_array<u_char>& packet )
{
    _pcapHeader = head;
    _packet = packet;
}

void RawPacket::setPacket ( const pcap_pkthdr* head, const u_char* packet )
{
    _pcapHeader.reset ( ( pcap_pkthdr* ) head );
    _packet.reset ( ( u_char* ) packet );
}

void RawPacket::initialisePacket ( const u_int32_t& length )
{
    _packet.reset ( new u_char[length] );
    _pcapHeader.reset ( new pcap_pkthdr );
    _pcapHeader->len = length;
    _pcapHeader->caplen = length;
}

void RawPacket::insert( const vector<u_char>& data,
    const bpf_u_int32& from_position, const bpf_u_int32& length,
    const bpf_u_int32& position )
{
    if ( ( data.size() >= (length + from_position) ) &&
        ( _pcapHeader->len >= (position + length) ) )
    {
        vector<u_char>::const_iterator from = data.begin() + from_position;
        u_char* to = _packet.get() + position;
        __gnu_cxx::copy_n( from, length, to );
    }
}

//const shared_array<u_char>& RawPacket::getPacket() const
//{
//    return _packet;
//}

//const bpf_u_int32& RawPacket::getPacketLength() const
//{
//    return _pcapHeader->len;
//}
