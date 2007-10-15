#ifndef __PACKETDUMPER_HH__
#define __PACKETDUMPER_HH__

#include <QtCore>
#include <QString>

#include <pcap.h>

#include <boost/shared_ptr.hpp>

#include "lockablequeue.hh"

using boost::shared_ptr;

class RawPacket;

/*!
The PacketDumper is a dedicated thread to dump packets to file.

\author Simon Jagoe
*/
class PacketDumper: public QThread
{
    Q_OBJECT
    public:
        /*!
        Construct a PacketDumper and prepare it to dump packets.

        \param linkType The Link Layer Type of the packets being dumped
        (pcap parameter).
        \param captureLength Size to trim each packet to (pcap parameter).
        \param file File name of the dump file
        \param enabled Enable or disable the packet dumping functionality.
        */
        PacketDumper( int linkType,
            int captureLength,
            QString file,
            bool enabled = true );
        ~PacketDumper();

        /*!
        Called by the statistics layer to add packets to the dump queue.

        \param packet RawPacket to be dumped to file.
        */
        void savePacket( const shared_ptr<RawPacket>& packet );

        /*!
        Perform the actual dumping in a thread.
        */
        void run();

        /*!
        Stop the thread and end dumping.
        */
        void stop();

        /*!
        Return the number of packets waiting to be dumped to disk.

        \return Number of packets in the dump queue waiting to be dumped to
        disk.
        */
        int waitingPackets();

    private:
        //! boolean to determine the state of the thread, and exit if required
        bool _running;

        //! is packet dumping enabled
        bool _enabled;

        //! Indicate that packets are waiting to be processed
        QSemaphore _packetsWaiting;

        //! Mutex used by the wait condition to mak ethe thread sleep
        QMutex _waitMutex;

        //! wait condition to make the thread sleep and signal it to wake up
        QWaitCondition _wait;

        //! Queue for packets to be processed
        LockableQueue<shared_ptr<RawPacket> > _packetQueue;

        //! Paramater for opening the dummy interface
        int _linkType;

        //! Paramater for opening the dummy interface
        int _captureLength;

        //! Filename of the dump file
        QString _file;

        //! dummy interface used for the dump
        pcap_t* _dumpInterface;

        //! file used for the dump
        pcap_dumper_t* _dumpFile;
};

#endif
