#ifndef __RAWPACKET_HH__
#define __RAWPACKET_HH__

// boost
#include <boost/shared_ptr.hpp>
#include <boost/shared_array.hpp>
#include <boost/scoped_ptr.hpp>

// pcap
#include <pcap.h>

#include "interfaceroute.hh"

using boost::shared_array;
using boost::shared_ptr;
//using boost::scoped_ptr;

class Device;

/*!
The Packet class provides a pointer-free encapsulation of (most of) the data
provided by the libpcap packet capture interface.

The libpcap capture library provides a pointer to a packet metadata header, and
a pointer to an array of the packet data. The header details the length of the
packet, and some other (ignored) information.

This class encapsulates the provided pcap pointer array in a
boost::shared_array, and the header in a boost::shared_ptr.

\author Simon Jagoe
*/

class RawPacket
{
    private:
        //! A byte (unsigned char) array containing the actual packet data.
        shared_array<u_char> _packet;

        //! a pcap_pktheader containing information about the packet (such as length)
        shared_ptr<pcap_pkthdr> _pcapHeader;

        //! An InterfaceRoute containing routing information for the packet
        shared_ptr<InterfaceRoute> _interfaceRoute;

    public:
        /*!
        Create an empty InterfaceRoute and pcap_pkthdr
        */
        RawPacket();

        /*!
        Create a RawPacket containing the packet data in the method arguments.

        \param head A pcap_pkthdr containing metadata describing the packet.
        \param packet A byte array of the actual packet data (captured by
        libpcap).
        \param sourceDevice The Device that the packet was captured on.
        */
        RawPacket ( const pcap_pkthdr* head, const u_char* packet,
                    const shared_ptr<Device>& sourceDevice );

        /*!
        Create a RawPacket containing the packet data in the method arguments.

        \param head A pcap_pkthdr containing metadata describing the packet.
        \param packet A byte array of the actual packet data (captured by
        libpcap).
        \param sourceDevice The Device that the packet was captured on.
        */
        RawPacket ( const shared_ptr<pcap_pkthdr>& head,
                    const shared_array<u_char>& packet,
                    const shared_ptr<Device>& sourceDevice );

//        void setPacket( bpf_u_int32 length, vector<u_char> packet );
//        void append(vector<u_char> data);
//        void append(u_char data);

        /*!
        Set the packet data to that provided in the arguments.

        \param head A pcap_pkthdr containing metadata describing the packet.
        \param packet A byte array of the actual packet data (captured by
        libpcap).
        */
        void setPacket ( const pcap_pkthdr* head, const u_char* packet );

        /*!
        Set the packet data to that provided in the arguments.

        \param head A pcap_pkthdr containing metadata describing the packet.
        \param packet A byte array of the actual packet data (captured by
        libpcap).
        */
        void setPacket ( const u_char* packet, const u_int32_t& length );

        /*!
        Initialise the packet array to a new, empty array of length \a length.
        */
        void initialisePacket ( const u_int32_t& length );

//        void insert( const vector<u_char>& data,
//            const bpf_u_int32& from_position, const bpf_u_int32& length,
//            const bpf_u_int32& position );

        /*!
        Add a destination to the InterfaceRoute.

        \param destinationInterface A Device that the packet will be
        transmitted on
        */
        void addDestination( const shared_ptr<Device>& destinationInterface );

        /*!
        Return the boost shared_array containing the packet data.

        \return Reference to a boost::shared_array<unsigned char> containing
        the raw packet data.
        */
        inline const shared_array<u_char>& getPacket() const
        {
            return _packet;
        };

        /*!
        Return the boost shared_ptr containing the pcap packet header

        \return Reference to a boost::shared_ptr<pcap_pkthdr>
        */
        inline const shared_ptr<pcap_pkthdr>& getHeader() const
        {
            return _pcapHeader;
        };

        /*!
        Return the length of the packet specified in the pcap_pkthdr.

        \return A 32-bit unsigned integer specifying the length.
        */
        inline const bpf_u_int32& getPacketLength() const
        {
            return _pcapHeader->len;
        };

        /*!
        Return a reference to the smart_ptr to the InterfaceRoute.

        The InterfaceRoute is stored in a boost::scoped_ptr, and cannot be
        copied.

        \return A boost::shared_ptr to the InterfaceRoute.
        */
        inline shared_ptr<InterfaceRoute>& getInterfaceRoute()
        {
            return _interfaceRoute;
        };

        /*!
        Return the raw \code unsigned char* \endcode pointer to the packet data
        array.

        \return Raw pointer to the packet data array.
        */
        inline u_char* getPacketPointer()
        {
            return _packet.get();
        };
};

#endif
