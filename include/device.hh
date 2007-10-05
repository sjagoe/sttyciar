#ifndef __DEVICE_H__
#define __DEVICE_H__

#include <string>
#include <QList>
#include <boost/shared_ptr.hpp>
#include <pcap.h>
#include "deviceaddress.hh"
#include "lockablequeue.hh"
#include "rawpacket.hh"
#include "pcapreceivethread.hh"
#include "pcapsendthread.hh"
#include "exceptions.hh"
#include "alnetworklistener.hh"

using namespace std;
using boost::shared_ptr;
using boost::weak_ptr;

/*!
This class represents a device retrieved from the <a href="http://www.winpcap.org/docs/docs_40_1/html/group__wpcapfunc.html#g7b128eaeef627b408f6a6e2a2f5eb45d">pcap_findalldevs</a> function.
A Device contains all the information retrieved from a <a href="http://www.winpcap.org/docs/docs_40_1/html/structpcap__if.html">pcap_if struct</a>.

\author Doron Horwitz
*/
class Device
{
    public:
        /*!
        Default constructor
        */
        Device();

        /*!
        Copy constructor. This provides a deep copy of the Device object except for the PcapSendThread and PcapReceiveThread
        members - the produced copy will contain a pointer to the same PcapSendThread and PcapReviceThread as the original.

        \param device The original device
        */
        Device(const Device& device);

        /*!
        Construct a Device based on a <a href="http://www.winpcap.org/docs/docs_40_1/html/structpcap__if.html">pcap_if struct</a>.

        \param pcapDevice The pcap_if device containing the information to be copied into the Device.
        */
        Device(pcap_if* pcapDevice);

        /*!
        Allow the Device to have a reference to itself. Used only at a low level to provide a mechanism for
        the PcapSendThread contained in this Device to know about this Device.

        \param self a boost::weak_ptr to the same Device
        */
        void setSelf(weak_ptr<Device>& self);

        /*!
        Update the device to contain the same informatin contained in a <a href="http://www.winpcap.org/docs/docs_40_1/html/structpcap__if.html">pcap_if struct</a>.

        \param pcapDevice The pcap_if device containing the information to be copied into the Device.
        */
        void setContents(pcap_if* pcapDevice);

        /*!
        Get the unique identifying name of the Device as provided by libpcap.

        \return The name of the device
        */
        string getName() const;

        /*!
        Get the description of the Device provided by libpcap

        \return The description of the Device
        */
        string getDescription() const;

        /*!
        Get a list of addresses (in the form of DeviceAddress) associated with this device. Yes, it is possible
        for a Device to have more than one address.

        \return The list of addresses.
        \sa DeviceAddress
        */
        const QList<DeviceAddress>& getAddresses() const;

        /*!
        Find out if the Device is a loopback interface

        \return \e true if the Device is loopback, otherwise \e false.
        */
        bool isLoopback() const;

        /*!
        Find out if two devices are equivalent. To devices are deemed equivalent if their
        names are the equal.

        \return \e true if the Devices are equivalent, otherwise \e false.
        */
        bool operator==(Device& device) const;

        /*!
        Open the device for capturing and sets the pcap capture filter if required
        \param packetCaptureSize The maximum size of the packet to be captured. If a packet contains
        more than \e packetCaptureSize bytes, it will be ignored.
        \param timeout How long to wait for packets to arrive before they are processed. This parameter
        also affects how long it takes for AbstractionLayer::stopListening() function to execute as it will
        block until the timeout has occured.
        \param alNetworkListener The object that will handle packets received from the network
        \param filterEnabled A boolean indicated if the pcap capture filter should be enabled on this device
        \throw CannotOpenDeviceException if a libpcap reports an error whilst trying to open the Device
        */
        void open(int packetCaptureSize,int timeout,weak_ptr<ALNetworkListener>& alNetworkListener,bool filterEnabled) throw (CannotOpenDeviceException);

        /*!
        Close the Device if it has an open pcap capture interface.
        */
        void close();

        /*!Start the threads listening for send and receive requests. This function should not be called directly
        as it is called by AbstractionLayer::startListening(int,int)

        \throw CannotStartListeningException if devices were not opened before this was called
        */
        void startListening() throw (CannotStartListeningException);


        /*!
        Stop the device listening. This kills the threads which handle sent and received packets.
        This function should not be called directly as it is called by AbstractionLayer::stopListening().
        This function also close the pcp capture instance.
        */
        void stopListening();

        /*!
        Send a RawPacket over the network. This function should not be called directly as it is called by
        AbstractionLayer::sendDataLinkLayerPacket(shared_ptr<DataLinkLayerPacket >) or AbstractionLayer::sendNetworkLayerPacket(shared_ptr<NetworkLayerPacket>).
        Also this function can only be called when this Device's PcapSendThread is running.

        \param The RawPacket to be sent over the network.
        */
        void sendPacket(const shared_ptr<RawPacket>& packet);

        /*!
        This represents the open pcap capture instance for this Device. This is only useful whilst the receiving and sending threads
        are running, as it does not exists at other times.

        \return The currently open pcap capture instance
        */
        pcap_t* getPcapSource();

    private:
        string _name; //!The name of the Device according to libpcap
        string _description; //!The description of the Device according to libpcap
        QList<DeviceAddress> _addresses; //!The list of addresses (DeviceAddress) associated with this Device
        shared_ptr<PcapSendThread> _pcapSendThread; //!The thread object used to handle packets waiting to be sent on this Device
        shared_ptr<PcapReceiveThread> _pcapReceiveThread; //!The thread object used to handle packets which have been received on this Device
        unsigned int _flags; //!The flags representing various modes of this Device, according to libpcap
        pcap_t* _pcapSource; //!The open capture instance associated with this Device when it is handling packets
        weak_ptr<Device> _self; //!A Device's reference to itself
        char _pcapErrorBuffer[PCAP_ERRBUF_SIZE]; //!The error buffer used by libpcap to indicate the nature of any pcap errors
        bool _isOpened; //!Indicates whether a device is open or not

        /*!
        Used to create a QList of DeviceAddress from the link list generated by libpcap.
        */
        void createAddressList(pcap_if* pcapDevice);

        /*!
        Set the pcap packet filter to ignore packets destinted for this device's own interface
        */
        void setFilter() throw (PcapFilterException);
};

#endif // DEVICE_H
