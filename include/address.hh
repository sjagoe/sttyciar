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
*/
class Address
{
    public:

        /*!
        The defaul constructor which does nothing
        */
        Address();

        /*!
        Constructs an Address based on a system defined IPv4 sockaddr_in struct

        \param socketAddress a sockaddr_in representation of the address
        */
        Address(sockaddr_in* socketAddress);

        /*!
        Constructs an Address based on a system defined sockaddr struct

        \param socketAddress a sockaddr representation of the address
        */
        Address(sockaddr* socketAddress);
        Address(uint8_t* address,int size);
        //static const int DEFAULT_ADDRESS_LENGTH = 16;
        void setContents(sockaddr_in* socketAddress);
        void setContents(sockaddr* socketAddress);
        void setContents(uint8_t* address,int size);
        const shared_array<uint8_t>& getByteAddress();
        int getSize() const;
        uint8_t getAddressByte(const int i) const;
        string toIPString() const;
        uint8_t operator[](const int i);

    private:
        shared_array<uint8_t> _address;
        int _size; //this indicates the amount of space actually being used

};

#endif // ADDRESS_H
