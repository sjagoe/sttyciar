#ifndef __PACKET_HH__
#define __PACKET_HH__

#include <boost/shared_ptr.hpp>

using boost::shared_ptr;

class RawPacket;

class Packet
{
    protected:
        shared_ptr<RawPacket> _rawPacket;

        void setRawPacket( shared_ptr<RawPacket>& rawPacket )
        {
            _rawPacket = rawPacket;
        };

    public:
        ~Packet()
        {
            _rawPacket.reset();
        };

        const shared_ptr<RawPacket>& getRawPacket() const
        {
            return _rawPacket;
        };

};

#endif
