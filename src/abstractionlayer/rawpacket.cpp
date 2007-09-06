//#include <algorithm>
#include <ext/algorithm>

#include "rawpacket.hh"

RawPacket::RawPacket()
{
    _packetLength = 0;
}

RawPacket::RawPacket( const pcap_pkthdr* head, const u_char* data )
{
    if ((head) && (data))
    {
        //this->packet.resize(head->len, 0); // (unnecessary?) overhead
        //if (data) // if the above line is not needed,
        // this check can be performed with the (head) check.
        {
            _packet.resize(head->len);
            __gnu_cxx::copy_n(data, head->len, _packet.begin());
            _packetLength = head->len;
            //pkthdr = *head;
        }
    }
}

void RawPacket::setPacket( bpf_u_int32 length, vector<u_char> packet )
{

};

void RawPacket::append(vector<u_char> data)
{

};
