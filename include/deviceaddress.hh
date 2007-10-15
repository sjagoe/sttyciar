#ifndef __DEVICEADDRESS_H__
#define __DEVICEADDRESS_H__

#if defined(WIN32) // if Win32 platform
#include <winsock.h>
//#elif defined() // if MS-DOS platform
#else // *NIX platforms
#endif // endif Win32/DOS/*NIX

#include <ext/algorithm>
#include <pcap.h>
#include "address.hh"

/*!
This class represents an address of a Device. The address includes the ip address, the netmask, the broadcast address
and the destination address which are all retrieved from libpcap. The addresses are stored as Address objects.
*/
class DeviceAddress
{
    public:
        /*!
        Default constructor
        */
        DeviceAddress();

        /*!
        Construct a DeviceAddress from a <a href="http://www.winpcap.org/docs/docs_40_1/html/structpcap__addr.html">pcap_addr struct</a>
        retrieved from libpcap.

        \param pcapAddress A pcap_addr struct containing the information to be stored in the DeviceAddress
        */
        DeviceAddress(pcap_addr* pcapAddress);

        /*!
        Set the contents of a DeviceAddress to those specified in a <a href="http://www.winpcap.org/docs/docs_40_1/html/structpcap__addr.html">pcap_addr struct</a>
        retrieved from libpcap.

        \param pcapAddress A pcap_addr struct containing the information to be stored in the DeviceAddress
        */
        void setContents(pcap_addr* pcapAddress);

        /*!
        Get the IP address

        \return The IP address as an Address object
        */
        const Address& getAddress() const;

        /*!
        Get the netmask

        \return The netmask as an Address object
        */
        const Address& getNetmask() const;

        /*!
        Get the broadcast address

        \return The broadcast address as an Address object
        */
        const Address& getBroadcastAddress() const;

        /*!
        Get the IP address

        \return The IP address as an Address object
        */
        const Address& getDestinationAddress() const;

    private:
        //! The IP address
        Address _addr;

        //! The netmask
        Address _netmask;

        //! The broadcast address
        Address _broadAddr;

        //! The destination address
        Address _dstAddr;

        //!Used by DeviceAddress::copySockAddr(sockaddr,sockaddr) to define the length of the address
        static const int DEFAULT_ADDRESS_LENGTH = 14;

        /*!Utility function to copy one <a href="http://msdn2.microsoft.com/en-us/library/ms740496.aspx">sockaddr struct</a> into another

        \param src The source sockaddr
        */
        static void copySockAddr(sockaddr &src, sockaddr &dst);
};


#endif // ADDRESS_H_INCLUDED
