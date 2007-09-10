#ifndef __NLLLISTENER_HH__
#define __NLLLISTENER_HH__

class DataLinkLayerPacket;
class NetworkLayerPacket;
class ALNetworkListener;

class NLLListener
{
    public:
        /*!
        send a data link layer frame (i.e. all headers and payload is
        contained, and the AL can send it without modification)
        */
        virtual void sendDataLinkLayerPacket( DataLinkLayerPacket& packet,
            InterfaceRoute& interfaces ) = 0;

        /*!
        send a network layer frame (i.e. the network layer [IP] header and
        payload is contained, and the AL needs to calculate the DLL header)
        */
        virtual void sendNetworkLayerPacket( NetworkLayerPacket& packet,
            InterfaceRoute& interfaces ) = 0;

        /*!
        register an ALListener (i.e. NLL module) with the AL.
        */
        virtual void registerNLL( ALNetworkListener& nllModule ) = 0;
};

#endif
