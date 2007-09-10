#ifndef ADDRESS_H
#define ADDRESS_H

#include <string>
#include <winsock.h>
#include <boost/array.hpp>

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
