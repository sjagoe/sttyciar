#ifndef ADDRESS_H
#define ADDRESS_H

#if defined(WIN32) // if Win32 platform
    #include <winsock.h>
#else // *NIX platforms
    #include <pcap.h>

    #include <sys/socket.h>
    #include <linux/in.h>
#endif // endif Win32/*NIX

#include <string>
#include <boost/shared_array.hpp>


/*!
A struct containing an IP address in 3 different formats in a union called s_un
1) S_un_b contains four bytes of an IP Address: s_b1, s_b2, s_b3, s_b4
2) S_un_w contains the IP address in 2 16 bit numbers: s_w1, s_w2
3) S_addr contains the IP address in a single 32 bits number
*/
struct in_addr_windows
{
    union
    {
        struct
        {
            u_char s_b1,s_b2,s_b3,s_b4;
        } S_un_b;
        struct
        {
            u_short s_w1,s_w2;
        } S_un_w;
        u_long S_addr;
    } S_un;
};

using namespace std;
using boost::shared_array;

/*!
This is a generic container for a network address (eg MAC or IP) of any length.

\author Doron Horwitz
*/
class Address
{
    public:

        /*!
        The default constructor which does nothing
        */
        Address();

        /*!
        Constructs an Address based on a system defined IPv4 sockaddr_in struct.
        In the Win32 environment see <a href="http://msdn2.microsoft.com/en-us/library/ms740496.aspx">winsock.h</a> for more information

        \param socketAddress a sockaddr_in representation of the address
        */
        Address(sockaddr_in* socketAddress);

        /*!
        Constructs an Address based on a system defined sockaddr struct
        In the Win32 environment see <a href="http://msdn2.microsoft.com/en-us/library/ms740496.aspx">winsock.h</a> for more information

        \param socketAddress a sockaddr representation of the address
        */
        Address(sockaddr* socketAddress);

        /*!
        Consructs an Address using an array of bytes. The size of the array must also be specified
        as the size of the array is undefined in the Address class.

        \param address The address, where the byte at index 0 is the left most value in the address
        e.g. In the address 192.168.0.4, 192 would be the byte at index 0.
        \param size The amount of bytes in the address.
        */
        Address(uint8_t* address,int size);
        //static const int DEFAULT_ADDRESS_LENGTH = 16;

        /*!
        Sets the contents of the Address based on a system defined IPv4 sockaddr_in struct.
        In the Win32 environment see <a href="http://msdn2.microsoft.com/en-us/library/ms740496.aspx">winsock.h</a> for more information

        \param socketAddress a sockaddr_in representation of the address
        */
        void setContents(sockaddr_in* socketAddress);

         /*!
        Sets contents of the Address based on a system defined sockaddr struct
        In the Win32 environment see <a href="http://msdn2.microsoft.com/en-us/library/ms740496.aspx">winsock.h</a> for more information

        \param socketAddress a sockaddr representation of the address
        */
        void setContents(sockaddr* socketAddress);

        /*!
        Sets the contents of the Address using an array of bytes. The size of the array must also be specified
        as the size of the array is undefined in the Address class.

        \param address The address, where the byte at index 0 is the left most value in the address
        e.g. In the address 192.168.0.4, 192 would be the byte at index 0.
        \param size The amount of bytes in the address.
        */
        void setContents(uint8_t* address,int size);

        /*!
        Get the address as a <a href="http://www.boost.org/libs/smart_ptr/shared_array.htm">boost::shared_array</a>

        \return The address in bytes stored in an array.
        */
        const shared_array<uint8_t>& getByteAddress();

        /*!
        Get the amount of bytes in the address.

        \return The amount of bytes in the address
        */
        int getSize() const;

        /*!
        Get a single byte from the address. If the index is greater than the amount of bytes in the Address,
        then a 0 is returned.

        \param i The index of the byte to be returned
        \return The byte value at the specified index
        */
        uint8_t getAddressByte(const int i) const;

        /*!
        Construct a IPv4 address string. This assumes that an IPv4 address is stored in the Address
        \return The address formatted as an IPv4 address
        */
        string toIPString() const;

        /*!
        Has the same affect as Address::getAddressByte(i).

        \param i The index of the byte to be returned
        \return The byte value at the specified index
        */
        uint8_t operator[](const int i);

    private:
        shared_array<uint8_t> _address; //! The bytes stored in the Address
        int _size; //! This indicates the amount of bytes stored in the _address member variable.

};

#endif // ADDRESS_H
