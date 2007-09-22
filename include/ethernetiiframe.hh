#ifndef __ETHERNETIIFRAME_HH__
#define __ETHERNETIIFRAME_HH__


#include <sys/types.h>
//#include <vector>

#include <boost/shared_array.hpp>
#include <boost/shared_ptr.hpp>

#include "packetaccess.hh"

#include "datalinklayerpacket.hh"

//using std::vector;
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

        mac_t* _sourceMAC;
        mac_t* _destMAC;
        ethertype_t* _etherType;

    public:
        /*!
        Extract the header information and payload from
        a RawPacket object.

        @param packet The Packet object containing the raw packet data
        */
        EthernetIIFrame( shared_ptr<RawPacket>& packet );

        void setSourceMAC( const mac_t& mac );

        void setDestinationMAC( const mac_t& mac );

        void setEtherType( const ethertype_t& et );

        inline const int getPayloadOffset() const
        {
            return ETHERNETII_HEAD_LENGTH;
        };

        const mac_t& getSourceMAC() const;

        const mac_t& getDestinationMAC() const;

        const ethertype_t& getEtherType() const;

        // EtherTypes
        static const u_short ETHERTYPE_IPV4 = 0x0800;
        static const u_short ETHERTYPE_ARP = 0x0806;

};

#endif
