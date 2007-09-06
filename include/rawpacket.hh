#ifndef __RAWPACKET_HH__
#define __RAWPACKET_HH__

#include <vector>
#include <pcap.h>

#include "defines.hh"

using std::vector;

/*!
The Packet class provides a pointer-free encapsulation of (most of) the data
provided by the libpcap packet capture interface.

The libpcap capture library provides a pointer to a packet metadata header, and
a pointer to an array of the packet data. The header details the length of the
packet, and some other (ignored) information.

The Packet class stores the packet data in a vector (to dispose of the
pointer-based array), and the packet length.

@author Simon Jagoe
*/

class RawPacket
{
    private:
        vector<u_char> packet;
        bpf_u_int32 packetLength;
        //pcap_pkthdr pkthdr;

    public:
        RawPacket( const pcap_pkthdr* head, const u_char* data );

        inline const vector<u_char>& getPacket()
        {
            return packet;
        };

        inline const bpf_u_int32& getPacketLength()
        {
            return packetLength;
            //return pkthdr.len;
        };
};

#endif
