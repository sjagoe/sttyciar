#ifndef __PCAPSENDTHREAD_HH__
#define __PCAPSENDTHREAD_HH__

#include <string>
//#include <iostream>
#include <QtCore>
#include <boost/shared_ptr.hpp>
#include "pcap.h"
#include "lockablequeue.hh"

using boost::shared_ptr;
using std::string;

class RawPacket;

/*!
The thread which handles sending pcakets to the network. A separate PcapSendThread is required for each
Device which is sending data to the network. The thread is implemented as a <a href="http://doc.trolltech.com/4.0/qthread.html">QThread</a>
which run a loop that continuously dequeues packets off a buffer and sends them to the network. Packets are added to the
the buffer from an external thread.

\author Doron Horwitz
*/
class PcapSendThread : public QThread
{
    Q_OBJECT

    public:
        /*!
        Default constructor
        */
        PcapSendThread();

        /*!
        A constructor which indicates which capture instance to use for sending packets

        \param pcapSource The capture instance which represents the physical device which will be used to send packets
        */
        PcapSendThread(pcap_t* pcapSource);

        /*!
        Destructor
        */
        ~PcapSendThread();

        /*!
        Set the pcap capture instance which will be used for send packets.

        \param pcapSource The capture instance which represents the physical device which will be used to send packets
        */
        void setSource(pcap_t* pcapSource);

        /*!
        Add a packet to the buffer to be later processed and sent in the thread

        \param packet The RawPacket to be sent to the network
        */
        void addPacket(const shared_ptr<RawPacket>& packet);

        /*!
        Called from an external thread to stop the PcapSendThread running
        */
        void stopRunning();

    protected:
        /*!
        The implemented run() function required by the <a href="http://doc.trolltech.com/4.0/qthread.html">QThread</a> class.
        This function contains all the logic of sending packets using libpcap
        */
        void run();

    private:
        //! The send buffer
        LockableQueue<shared_ptr<RawPacket> > _packetQueue;

        //!A flag used by the loop in the run() function to indicate that the thread must continue running. Can be made false using PcapReceiveThread::stopRunning()
        bool _running;

        //!Used to prevent deadlocks and other concurrent programming problems
        QWaitCondition _waitCondition;

        //!Used to prevent deadlocks and other concurrent programming problems
        QMutex _mutex;

        //!The pcap capture interface used for sending packets
        pcap_t *_pcapSource;

        //!The array buffer to be used by libpcap in the case of an error occuring
        char _pcapErrorBuffer[PCAP_ERRBUF_SIZE];
};

#endif // __PCAPSENDTHREAD_HH__
