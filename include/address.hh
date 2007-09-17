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

class Address
{
    public:
        Address();
        Address(sockaddr_in* socketAddress);
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
