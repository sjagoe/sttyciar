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
#include <boost/array.hpp>

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
using boost::array;

class Address
{
    public:
        Address();
        Address(sockaddr_in* socketAddress);
        Address(sockaddr* socketAddress);
        static const int DEFAULT_ADDRESS_LENGTH = 16;
        void setContents(sockaddr_in* socketAddress);
        void setContents(sockaddr* socketAddress);
        const array<uint8_t,DEFAULT_ADDRESS_LENGTH>& getByteAddress();
        int getSize() const;
        uint8_t getAddressByte(const int i) const;

    private:
        array<uint8_t,DEFAULT_ADDRESS_LENGTH> _address;
        int _size; //this indicates the amount of space actually being used

};

#endif // ADDRESS_H
