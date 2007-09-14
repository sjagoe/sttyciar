#ifndef __ABSTRACTIONLAYER_HH__
#define __ABSTRACTIONLAYER_HH__

#include <vector>
#include <list>
#include <boost/shared_ptr.hpp>
#include "pcap.h"
//#include "nlllistener.hh"
#include "device.hh"
#include "exceptions.hh"

using std::vector;
using std::list;
using boost::shared_ptr;

class ALNetworkListener;
class DataLinkLayerPacket;
class NetworkLayerPacket;
class InterfaceRoute;

class QWaitCondition;
class QSemaphore;

class AbstractionLayer//: public NLLListener
{
    public:
        /*!
        Default Constructor creates required onjects (QWaitCondition and
        QSemaphore).
        */
        AbstractionLayer();

        /*!
        Constructor that sets the NLL module to interact with.
        */
        AbstractionLayer( shared_ptr<ALNetworkListener> nllModule );
        //AbstractionLayer( vector<shared_ptr<ALNetworkListener> > nllModules );

        /*!
        send a data link layer frame (i.e. all headers and payload is
        contained, and the AL can send it without modification)

        @param packet The DataLinkLayerPacket object containing the data.
        @param interfaces The InterfaceRoute object now containing full
        source/destination interface data.
        */
        void sendDataLinkLayerPacket( DataLinkLayerPacket& packet,
                                      InterfaceRoute& interfaces );

        /*!
        send a network layer frame (i.e. the network layer [IP] header and
        payload is contained, and the AL needs to calculate the DLL header)

        @param packet The NetworkLayerPacket object containing the data.
        @param interfaces The InterfaceRoute object now containing full
        source/destination interface data.
        */
        void sendNetworkLayerPacket( NetworkLayerPacket& packet,
                                     InterfaceRoute& interfaces );

        /*!
        register an ALNetworkListener (i.e. NLL module) with the AL.

        @param nllModule A NLL module (i.e. ALNetworkListener) that the AL can
        send messages to.
        */
        void registerNLL( shared_ptr<ALNetworkListener>& nllModule );

        /* !
        Unregister an ALNetworkListener (i.e. NLL module) with the AL.

        @param nllModule A NLL module (i.e. ALNetworkListener) that the AL can
        send messages to.
        */
        //void unregisterNLL( shared_ptr<ALNetworkListener>& nllModule );

        list<Device> getDevices() throw(DeviceNotFoundException);

        void activateDevice(Device device);
        bool isDeviceActivated(Device device);
        void startListening();

        shared_ptr<QWaitCondition>& getNLLWaitCondition();
        shared_ptr<QSemaphore>& getNLLSemaphore();

    private:
        char pcapErrorBuffer[PCAP_ERRBUF_SIZE];
        //vector<shared_ptr<ALNetworkListener> > _networkLogicLayer;
        list<Device> activatedDeviceNames;
        shared_ptr<ALNetworkListener> _networkLogicLayer;
        shared_ptr<QWaitCondition> _nllWaitCondition;
        shared_ptr<QSemaphore> _nllSemaphore;
};

#endif

