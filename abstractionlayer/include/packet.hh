#ifndef __PACKET_HH__
#define __PACKET_HH__

class RawPacket;

class Packet
{
    public:
        virtual ~Packet() {};
        virtual RawPacket getRawPacket() const = 0;

};

#endif
