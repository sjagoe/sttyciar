#ifndef __PACKETDUMPER_HH__
#define __PACKETDUMPER_HH__

#include <QtCore>
#include <QString>

#include <pcap.h>

#include <boost/shared_ptr.hpp>

#include "lockablequeue.hh"

using boost::shared_ptr;

class RawPacket;

class PacketDumper: public QThread
{
    Q_OBJECT
    public:
        PacketDumper( int linkType,
            int captureLength,
            QString file,
            bool enabled = true );
        ~PacketDumper();

        void savePacket( const shared_ptr<RawPacket>& packet );

        void run();

        void stop();

        int waitingPackets();

    private:
        bool _running; //! boolean to determine the state of the thread, and exit if required
        bool _enabled; //! is packet dumping enabled
        QSemaphore _packetsWaiting; //! Indicate that packets are waiting to be processed
        QMutex _waitMutex; //! Mutex used by the wait condition to mak ethe thread sleep
        QWaitCondition _wait; //! wait condition to make the thread sleep and signal it to wake up
        LockableQueue<shared_ptr<RawPacket> > _packetQueue; //! Queue for packets to be processed
        int _linkType; //! Paramater for opening the dummy interface
        int _captureLength; //! Paramater for opening the dummy interface

        QString _file; //! Filename of the dump file

        pcap_t* _dumpInterface; //! dummy interface used for the dump
        pcap_dumper_t* _dumpFile; //! file used for the dump
};

#endif
