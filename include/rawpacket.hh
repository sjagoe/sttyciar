#ifndef __RAWPACKET_HH__
#define __RAWPACKET_HH__

// STL
#include <vector>
#include <iterator>

// boost
#include <boost/shared_ptr.hpp>
#include <boost/shared_array.hpp>
#include <boost/scoped_ptr.hpp>

// pcap
#include <pcap.h>

using std::vector;
using boost::shared_array;
using boost::shared_ptr;
using boost::scoped_ptr;

class Device;
class InterfaceRoute;

/*!
The Packet class provides a pointer-free encapsulation of (most of) the data
provided by the libpcap packet capture interface.

The libpcap capture library provides a pointer to a packet metadata header, and
a pointer to an array of the packet data. The header details the length of the
packet, and some other (ignored) information.

This class encapsulates the provided pcap pointer array in a
boost::shared_array, and the header in a boost::shared_ptr.

@author Simon Jagoe
*/

class RawPacket
{
    private:
        shared_array<u_char> _packet;
        shared_ptr<pcap_pkthdr> _pcapHeader;
        scoped_ptr<InterfaceRoute> _interfaceRoute;

    public:
        RawPacket ( const pcap_pkthdr* head, const u_char* packet,
                    const shared_ptr<Device>& sourceDevice );
        RawPacket ( const shared_ptr<pcap_pkthdr>& head,
                    const shared_array<u_char>& packet,
                    const shared_ptr<Device>& sourceDevice );

        /*
        void setPacket( bpf_u_int32 length, vector<u_char> packet );
        void append(vector<u_char> data);
        void append(u_char data);
        */

        void setPacket ( const pcap_pkthdr* head, const u_char* packet );

        void initialisePacket ( const u_int32_t& length );

        void insert( const vector<u_char>& data,
            const bpf_u_int32& from_position, const bpf_u_int32& length,
            const bpf_u_int32& position );

        void addDestination( const shared_ptr<Device>& destinationInterface );

        inline const shared_array<u_char>& getPacket() const
        {
            return _packet;
        };

        inline const bpf_u_int32& getPacketLength() const
        {
            return _pcapHeader->len;
        };

        inline scoped_ptr<InterfaceRoute>& getInterfaceRoute()
        {
            return _interfaceRoute;
        };
};

#endif
