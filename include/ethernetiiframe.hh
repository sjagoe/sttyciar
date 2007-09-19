#ifndef __ETHERNETIIFRAME_HH__
#define __ETHERNETIIFRAME_HH__


#include <sys/types.h>
#include <vector>

#include <boost/shared_array.hpp>
#include <boost/shared_ptr.hpp>

#include "packetaccess.hh"

#include "datalinklayerpacket.hh"

using std::vector;
using boost::shared_array;
using boost::shared_ptr;

class RawPacket;

//#define ETHERNETII_MAC_LENGTH 6
//#define ETEHRNETII_ETHERTYPE_LENGTH 2

typedef struct six_byte mac_t;
typedef struct two_byte ethertype_t;


/*!
EthernetIIFrame encapsulates the Ethernet II Frame header and payload with an
easy to use interface.

The EthernetIIFrame should be created with a RawPacket as an argument. It will
extract the Ethernet II header and payload from the raw packet data.

@author Simon Jagoe
*/

class EthernetIIFrame: public DataLinkLayerPacket
{
    private:
        static const int ETHERNETII_HEAD_LENGTH = 14;
        static const int ETHERNETII_MAC_LENGTH = 6;

        mac_t* _sourceMAC, *_destMAC;
        ethertype_t* _etherType;

    public:
        /*!
        Extract the header information and payload from
        a RawPacket object.

        @param packet The Packet object containing the raw packet data
        */
        EthernetIIFrame( shared_ptr<RawPacket>& packet );

        inline const int getPayloadOffset() const
        {
            return ETHERNETII_HEAD_LENGTH;
        };

        inline const mac_t& getSourceMAC() const
        {
            return *_sourceMAC;
        };

        inline const mac_t& getDestinationMAC() const
        {
            return *_destMAC;
        };

        inline const ethertype_t& getEtherType() const
        {
            return *_etherType;
        };

};

#endif
