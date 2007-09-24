#include "address.hh"
//#include <iostream>
#include <sstream>

//const int Address::DEFAULT_ADDRESS_LENGTH;

Address::Address()
{
}

Address::Address(sockaddr_in* socketAddress)
{
    this->setContents(socketAddress);
}

Address::Address(sockaddr* socketAddress)
{
    this->setContents((sockaddr_in*)socketAddress);
}

Address::Address(uint8_t* address,int size)
{
    this->setContents(address,size);
}

void Address::setContents(sockaddr_in* socketAddress)
{
//#if defined(WIN32) // If on Win32
//    this->_address[0]=socketAddress->sin_addr.S_un.S_un_b.s_b1;
//    this->_address[1]=socketAddress->sin_addr.S_un.S_un_b.s_b2;
//    this->_address[2]=socketAddress->sin_addr.S_un.S_un_b.s_b3;
//    this->_address[3]=socketAddress->sin_addr.S_un.S_un_b.s_b4;
//#else // If on *NIX
    this->_address.reset(new uint8_t[4]);
    struct in_addr_windows* sin_addr = (struct in_addr_windows*)
        &socketAddress->sin_addr;
    this->_address[0]=sin_addr->S_un.S_un_b.s_b1;
    this->_address[1]=sin_addr->S_un.S_un_b.s_b2;
    this->_address[2]=sin_addr->S_un.S_un_b.s_b3;
    this->_address[3]=sin_addr->S_un.S_un_b.s_b4;
//#endif // Win32/*NIX
    this->_size=4;
}

void Address::setContents(sockaddr* socketAddress)
{
    this->setContents((sockaddr_in*)socketAddress);
}

void Address::setContents(uint8_t* address,int size)
{
    this->_address.reset(address);
    this->_size=size;
}

const shared_array<uint8_t>& Address::getByteAddress()
{
    return this->_address;
}

int Address::getSize() const
{
    return this->_size;
}

uint8_t Address::getAddressByte(const int i) const
{
    if (i < this->_size)
        return this->_address[i];
    else
        return 0;
}

string Address::toIPString() const
{
    std::ostringstream sIPAddress;
    sIPAddress << (unsigned int)getAddressByte(0);
    sIPAddress << ".";
    sIPAddress << (unsigned int)getAddressByte(1);
    sIPAddress << ".";
    sIPAddress << (unsigned int)getAddressByte(2);
    sIPAddress << ".";
    sIPAddress << (unsigned int)getAddressByte(3);

    return sIPAddress.str();
}

uint8_t Address::operator[](const int i)
{
    return this->getAddressByte(i);
}

