#ifndef __PACKET_HH__
#define __PACKET_HH__

class RawPacket;

class Packet
{
    public:
        virtual RawPacket& getRawPacket() = 0;

};

#endif
