#ifndef __PCAPRECEIVETHREAD_HH__
#define __PCAPRECEIVETHREAD_HH__

#include <QtCore>
//#include <iostream>
#include <boost/shared_ptr.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include "pcap.h"
//#include "device.hh"
#include "exceptions.hh"
#include "lockablequeue.hh"


using boost::shared_ptr;
using boost::scoped_ptr;
using boost::weak_ptr;

class ALNetworkListener;
class RawPacket;
class InterfaceRoute;
class Device;
class PcapThreadTicket;

/*!
The thread object used to process packets received from the network. The thread is implemented as a <a href="http://doc.trolltech.com/4.0/qthread.html">QThread</a>
running libpcap's <a href="http://www.winpcap.org/docs/docs_40_1/html/group__wpcapfunc.html#g439439c2eae61161dc1efb1e03a81133">pcap_next_ex</a> function
repeatedly. The packets are then inserted into a buffer to be processed by the network logic layer.
A PcapReceiveThread object should not be created directly as it is created by an AbstractionLayer and in turn by a Device
when required.

\author Doron Horwitz

*/
class PcapReceiveThread : public QThread
{
    Q_OBJECT

    public:
        /*!
        Default constructor
        */
        PcapReceiveThread();

        /*!
        Constructor which indicates the Device on which the packet was received - this information is used
        by the network logic layer. This constructor also indicates the ALNetworkListener which will handle the
        incoming packet.

        \param device The Device from where the incoming packets will be received. This is usually the Device which
        actually contains the PcapReceiveThread - i.e. The Device contains the PcapReceiveThread which in turn contains
        the same Device.
        \param alNetworkListener The implementation of the network logic layer which will handle received packets
        */
        PcapReceiveThread( const shared_ptr<Device>& device,
                    weak_ptr<ALNetworkListener> alNetworkListener);


        /*!
        Object destructor.
        */
        ~PcapReceiveThread();

        /*!
        Set the current Device from where packets are being received.
        \param device The Device from where the incoming packets will be received. This is usually the Device which
        actually contains the PcapReceiveThread - i.e. The Device contains the PcapReceiveThread which in turn contains
        the same Device.
        */
        void setDevice(weak_ptr<Device>& device);

        /*!
        Set the alNetworkListener which will handle incoming network traffic
        \param alNetworkListener The implementation of the network logic layer which will handle received packets
        */
        void setALNetworkListener(weak_ptr<ALNetworkListener>& alNetworkListener);

        /*!
        Stop the PcapReceivedThread from running. This allows the thread to gracefully be shut down from another thread
        */
        void stopListening();

    protected:
        /*!
        The implemented run() function required by the <a href="http://doc.trolltech.com/4.0/qthread.html">QThread</a> class.
        This function contains all the logic of receving packets using libpcap

        \throw CannotOpenDeviceException if libpcap reports an error whilst attempting to open a pcap capture instance
        */
        void run() throw(CannotOpenDeviceException);
    private:
        weak_ptr<Device> _device; //!A pointer to the Device from where network packets will be received
        int _pcapPacketCaptureSize; //!The maximum size of a packet to be captured from the network layer
        int _pcapTimeout; //!How long to wait for packets before the <a href="http://www.winpcap.org/docs/docs_40_1/html/group__wpcapfunc.html#g439439c2eae61161dc1efb1e03a81133">pcap_next_ex()</a> function times out
        char _pcapErrorBuffer[PCAP_ERRBUF_SIZE]; //!The array buffer to be used by libpcap in the case of an error occuring
        bool _listening; //!A flag used by the loop in the run() function to indicate that the thread must continue running. Can be made false using PcapReceiveThread::stopListening()
        weak_ptr<ALNetworkListener> _alNetworkListener; //!The ALNetworkListener which will handle incoming network packets
        scoped_ptr<PcapThreadTicket> _receiveBuffer; //!The buffer which temporarily stores packets received from the network before they are processed.
};

#endif // __PCAPRECEIVETHREAD_HH__
