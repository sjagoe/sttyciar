#ifndef __PACKET_HH__
#define __PACKET_HH__

#include <vector>
#include <pcap.h>

#include "defines.hh"

using std::vector;

class Packet
{
    private:
        vector<u_char> packet;
        bpf_u_int32 payloadLength;

    public:
        Packet( const pcap_pkthdr* head, const u_char* data );

        inline const vector<u_char>& getPacket()
        {
            return packet;
        };
};

#endif
