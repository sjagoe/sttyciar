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
This class provides the interface to the libpcap library. It is used to retrieve information about netwrok
devices attached to the current system. It also provides the mechanism for sending and receiving packets to and
from the network and for defining which implementation of the ALNetworkListener interface will handle the routing
of packets.

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
        a call to the AbstractionLayer::startListening(int,int) function. If the device is already
        activated nothing will happen.

        \param device A device to be activated. This device must have the same name (given by the
        Device::getName() function) as a device in the system
        */
        void activateDevice(shared_ptr<Device>& device);

        /*!
        Activate a list of devices according to names. These activated devices will be
        used by the AbstractionLayer when AbstractionLayer::startListening(int,int) is called.

        \param devices A list of names of devices to be activated. The devices in this list will
        be activated if they actually exist in the system.
        */
        void activateDevices( shared_ptr<QStringList> devices );

        /*!
        Check whether a device has been activated or not.

        \return true if the device has been activated, false otherwise
        */
        bool isDeviceActivated(shared_ptr<Device>& device);

        /*! Get a list of pointers to the devices that have been activated

        \return a list of pointers to the activated devices
        */
        QList<shared_ptr<Device> > getActivatedDevices();

        /*!
        Start listening on all activated devices. This function must be called before
        attempting to send messages. Also, all packets arriving from the network will be processed
        once this function has been called.

        \param packetCaptureSize The maximum size of the packet to be captured. If a packet contains
        more than \e packetCaptureSize bytes, it will be ignored.
        \param timeout How long to wait for packets to arrive before they are processed. This parameter
        also affects how long it takes for AbstractionLayer::stopListening() function to execute as it will
        block until the timeout has occured.
        */
        void startListening(int packetCaptureSize,int timeout);

        /*!
        Stop listening for send and received packets. This function blocks until the timeout
        specified in the AbstractionLayer::startListening has elapsed.
        */
        void stopListening();

        /*!
        Enable the pcap packet filter to force pcap to ignore any packets destined for
        a device's ip address. Note: By default, the filter is disabled.

        \param filterEnabled True if filter must be enabled, false otherwise
        */
        void setFilterEnabled(bool filterEnabled);

    protected:
        /*!
        Get a pointer to the ALNetworkListener currently registered to handle packets received
        from the network

        \return A shared pointer to the currently registered ALNetworkListener
        */
        inline shared_ptr<ALNetworkListener> getNLL()
        {
            return _networkLogicLayer.lock();
        };

    private:
        char _pcapErrorBuffer[PCAP_ERRBUF_SIZE]; //! A buffer used by libpcap to contain an error message generated from any libpcap fucntion

        QList<shared_ptr<Device> > _devices; //!The devices attached to the system when the AbstracionLayer is created (i.e. this list is only filled when the constructor is called
        QList<shared_ptr<Device> > _activatedDevices; //!A list of devices which will be used to send and receive packet

        weak_ptr<ALNetworkListener> _networkLogicLayer; //!A pointer to the ALNetworkListener registered to handle packets received from the network
        shared_ptr<ALStatisticsListener> _statisticsLayer; //!A pointer to the ALStatisticsListener registered to handle routing statistics. This defaults to an implementation with empty overridden virtual functions

        bool _filterEnabled;

        /*!
        Used to initialize a list of network devices which are currently attached to the system. This function is called by
        the constructor and it is for that reason, that the list of devices does not change for the lifetime of an AbstractionLayer
        object.
        */
        void retrieveDevices() throw (DeviceNotFoundException);

};

#endif

