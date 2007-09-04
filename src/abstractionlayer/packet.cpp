//#include <algorithm>
#include <ext/algorithm>

#include "packet.hh"

Packet::Packet( const pcap_pkthdr* head, const u_char* data )
{
    if ((head) && (data))
    {
        //this->packet.resize(head->len, 0); // (unnecessary?) overhead
        //if (data) // if the above line is not needed,
        // this check can be performed with the (head) check.
        {
            __gnu_cxx::copy_n(data, head->len, this->packet.begin());
            payloadLength = head->len - ETHERNETII_HEAD_LENGTH;
        }
    }
}
