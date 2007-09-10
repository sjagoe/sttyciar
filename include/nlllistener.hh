#ifndef __NLLLISTENER_HH__
#define __NLLLISTENER_HH__

#include <vector>
#include <boost/shared_ptr.hpp>

using std::vector;

class DataLinkLayerPacket;
class NetworkLayerPacket;
class ALNetworkListener;


/*!
The NLLListener is a (pure virtual) public interface that is implemented by the
Abstraction Layer to allow any Network Logic Layer module to pass information
to it.

@author Simon Jagoe
*/
class NLLListener
{
    public:
        /*!
        Virtual destructor to allow destructor overriding.
        */
        virtual ~NLLListener() {};

        /*!
        send a data link layer frame (i.e. all headers and payload is
        contained, and the AL can send it without modification)

        @param packet The DataLinkLayerPacket object containing the data.
        @param interfaces The InterfaceRoute object now containing full
        source/destination interface data.
        */
        virtual void sendDataLinkLayerPacket( DataLinkLayerPacket& packet,
            InterfaceRoute& interfaces ) = 0;

        /*!
        send a network layer frame (i.e. the network layer [IP] header and
        payload is contained, and the AL needs to calculate the DLL header)

        @param packet The NetworkLayerPacket object containing the data.
        @param interfaces The InterfaceRoute object now containing full
        source/destination interface data.
        */
        virtual void sendNetworkLayerPacket( NetworkLayerPacket& packet,
            InterfaceRoute& interfaces ) = 0;

        /*!
        register an ALNetworkListener (i.e. NLL module) with the AL.

        @param nllModule A NLL module (i.e. ALNetworkListener) that the AL can
        send messages to.
        */
        virtual void
            registerNLL( shared_ptr<ALNetworkListener> nllModule ) = 0;

        /*!
        Unregister an ALNetworkListener (i.e. NLL module) with the AL.

        @param nllModule A NLL module (i.e. ALNetworkListener) that the AL can
        send messages to.
        */
        virtual void
            unregisterNLL( shared_ptr<ALNetworkListener> nllModule ) = 0;

    protected:
        vector<shared_ptr<ALNetworkListener> > _networkLogicLayer;
};

#endif
