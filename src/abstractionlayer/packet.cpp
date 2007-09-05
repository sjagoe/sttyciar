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
            this->packet.resize(head->len);
            __gnu_cxx::copy_n(data, head->len, this->packet.begin());
            packetLength = head->len;
            //pkthdr = *head;
        }
    }
}
