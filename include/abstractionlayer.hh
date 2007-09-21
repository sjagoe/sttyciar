#ifndef __ABSTRACTIONLAYER_HH__
#define __ABSTRACTIONLAYER_HH__

// STL
//#include <vector>

// Qt
#include <QList>
#include <QStringList>

// boost
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

// pcap
#include <pcap.h>

// local
#include "device.hh"
#include "exceptions.hh"

// import specific types from namespaces
//using std::vector;
using std::list;
using boost::shared_ptr;
using boost::weak_ptr;

// forward declerations
class ALNetworkListener;
class DataLinkLayerPacket;
class NetworkLayerPacket;
class InterfaceRoute;

class QWaitCondition;
class QSemaphore;
class RawPacket;
class PcapThread;

class AbstractionLayer//: public NLLListener
{
    public:
        /*!
        Default Constructor creates required onjects (QWaitCondition and
        QSemaphore).
        */
        AbstractionLayer();

        /*!
        send a data link layer frame (i.e. all headers and payload is
        contained, and the AL can send it without modification)

        @param packet The DataLinkLayerPacket object containing the data.
        @param interfaces The InterfaceRoute object now containing full
        source/destination interface data.
        */
        void sendDataLinkLayerPacket( shared_ptr<DataLinkLayerPacket> packet);

        /*!
        send a network layer frame (i.e. the network layer [IP] header and
        payload is contained, and the AL needs to calculate the DLL header)

        @param packet The NetworkLayerPacket object containing the data.
        @param interfaces The InterfaceRoute object now containing full
        source/destination interface data.
        */
        void sendNetworkLayerPacket( shared_ptr<NetworkLayerPacket> packet );

        /*!
        register an ALNetworkListener (i.e. NLL module) with the AL.

        @param nllModule A NLL module (i.e. ALNetworkListener) that the AL can
        send messages to.
        */
        void registerNLL( weak_ptr<ALNetworkListener>& nllModule );

        /* !
        Unregister an ALNetworkListener (i.e. NLL module) with the AL.

        @param nllModule A NLL module (i.e. ALNetworkListener) that the AL can
        send messages to.
        */
        //void unregisterNLL( shared_ptr<ALNetworkListener>& nllModule );

        QList<shared_ptr<Device> > getDevices();

        void activateDevice(shared_ptr<Device>& device);

        void activateDevices( shared_ptr<QStringList> devices );

        bool isDeviceActivated(shared_ptr<Device>& device);

        void startListening(int packetCaptureSize,int timeout);

        void stopListening();

        shared_ptr<QWaitCondition>& getNLLWaitCondition();

        shared_ptr<QSemaphore>& getNLLSemaphore();

    protected:
        inline shared_ptr<ALNetworkListener> getNLL()
        {
            return _networkLogicLayer.lock();
        };

    private:
        char _pcapErrorBuffer[PCAP_ERRBUF_SIZE];

        QList<shared_ptr<Device> > _devices;
        QList<shared_ptr<Device> > _activatedDevices;
        QList<shared_ptr<PcapThread> > _pcapThreads;

        bool _listening;
        weak_ptr<ALNetworkListener> _networkLogicLayer;

        shared_ptr<QWaitCondition> _nllWaitCondition;

        shared_ptr<QSemaphore> _nllSemaphore;
        void retrieveDevices() throw (DeviceNotFoundException);

};

#endif

