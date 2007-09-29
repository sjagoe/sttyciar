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
class ALStatisticsListener;
class DataLinkLayerPacket;
class NetworkLayerPacket;
class InterfaceRoute;

class QWaitCondition;
class QSemaphore;
class RawPacket;
class PcapReceiveThread;

/*!
This class provides the interface to the pcap library.

\author Simon Jagoe
\author Doron Horwitz
*/
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

        \param packet The DataLinkLayerPacket object containing the data.
        \param interfaces The InterfaceRoute object now containing full
        source/destination interface data.
        */
        void sendDataLinkLayerPacket( shared_ptr<DataLinkLayerPacket> packet);

        /*!
        send a network layer frame (i.e. the network layer [IP] header and
        payload is contained, and the AL needs to calculate the DLL header)

        \param packet The NetworkLayerPacket object containing the data.
        \param interfaces The InterfaceRoute object now containing full
        source/destination interface data.
        */
        void sendNetworkLayerPacket( shared_ptr<NetworkLayerPacket> packet );

        /*!
        register an ALNetworkListener (i.e. NLL module) with the AL.

        \param nllModule A NLL module (i.e. ALNetworkListener) that the AL can
        send messages to.
        */
        void registerNLL( weak_ptr<ALNetworkListener>& nllModule );

        /*!
        register an ALStatisticsListener (i.e. SLL module) with the AL.

        \param slModule A SL module (i.e. ALStatisticsListener) that the AL can
        send packet routing information to in order to update statistics.
        */
        void registerSL(shared_ptr<ALStatisticsListener> slModule);

        /* !
        Unregister an ALNetworkListener (i.e. NLL module) with the AL.

        \param nllModule A NLL module (i.e. ALNetworkListener) that the AL can
        send messages to.
        */
        //void unregisterNLL( shared_ptr<ALNetworkListener>& nllModule );


        /*!
        Return a list of network devices on the current system. Not all of these devices
        do not necessarily represent actual network devices. The returned list depends on
        the operating system. The ordering of the devices in the list is undefined.
        This list is remains constant for the lifetime if the abstractionlayer. So if new
        devices are added to the system when the AbstractionLayer is alread in existence, this
        function will return a list of devices <b>without</b> the newly added devices.

        \return A list of pointers to Devices in the system
        */
        QList<shared_ptr<Device> > getDevices();

        /*!
        Add a device that will be listened on when the abstraction layer starts running with
        a call to the AbstractionLayer::startListening(int,int) function.

        \param device A list of pointers to Devices in the system
        */
        void activateDevice(shared_ptr<Device>& device);

        void activateDevices( shared_ptr<QStringList> devices );

        bool isDeviceActivated(shared_ptr<Device>& device);

        QList<shared_ptr<Device> > getActivatedDevices();

        /*!
        Add a device that will be listened on when the abstraction layer starts running with
        a call to the AbstractionLayer::startListening() function.

        \param packetCaptureSize A list of pointers to Devices in the system
        \param timeout A list of pointers to Devices in the system
        */
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
        QList<shared_ptr<PcapReceiveThread> > _pcapThreads;

        bool _listening;
        weak_ptr<ALNetworkListener> _networkLogicLayer;
        shared_ptr<ALStatisticsListener> _statisticsLayer;

        shared_ptr<QWaitCondition> _nllWaitCondition;

        shared_ptr<QSemaphore> _nllSemaphore;
        void retrieveDevices() throw (DeviceNotFoundException);

};

#endif

