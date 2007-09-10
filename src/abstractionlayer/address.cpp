#include "address.hh"

const int Address::DEFAULT_ADDRESS_LENGTH;

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

void Address::setContents(sockaddr_in* socketAddress)
{
    this->_address[0]=socketAddress->sin_addr.S_un.S_un_b.s_b1;
    this->_address[1]=socketAddress->sin_addr.S_un.S_un_b.s_b2;
    this->_address[2]=socketAddress->sin_addr.S_un.S_un_b.s_b3;
    this->_address[3]=socketAddress->sin_addr.S_un.S_un_b.s_b4;
    this->_size=4;
}

void Address::setContents(sockaddr* socketAddress)
{
    this->setContents((sockaddr_in*)socketAddress);
}

const array<uint8_t,Address::DEFAULT_ADDRESS_LENGTH>& Address::getByteAddress()
{
    return this->_address;
}

int Address::getSize() const
{
    return this->_size;
}

uint8_t Address::getAddressByte(const int i) const
{
    return this->_address[i];
}
