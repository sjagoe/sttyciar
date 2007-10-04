//#include <iostream>
#include "packetdumper.hh"

#include "rawpacket.hh"
#include "ethernetiiframe.hh"

PacketDumper::PacketDumper( int linkType,
    int captureLength,
    QString file,
    bool enabled )
    : _linkType(linkType), _captureLength(captureLength), _file(file)
{
    // initialise members
    this->_enabled = enabled;
    this->_dumpInterface = 0;
    this->_dumpFile = 0;
    // if enabled, open the files etc.
    if (this->_enabled)
    {
        this->_running = true;
        this->_dumpInterface = pcap_open_dead( this->_linkType,
            this->_captureLength );
        if ( this->_dumpInterface != 0 )
        {
            this->_dumpFile =
                pcap_dump_open( this->_dumpInterface,
                    this->_file.toStdString().data() );
        }
        if ( (this->_dumpFile == 0) || ( this->_dumpInterface == 0 ) )
        {
            // exception
        }
    }
}

PacketDumper::~PacketDumper()
{

}

void PacketDumper::savePacket( const shared_ptr<RawPacket>& packet )
{
//    pcap_pkthdr* head = packet->getHeader().get();
//    std::cout << head->ts.tv_sec << "." << head->ts.tv_usec << std::endl;
    // if packet dumping is enabled, enqueue the packet for dumping
    if (this->_enabled)
    {
        this->_packetQueue.push( packet );
        // show that a packet has been enqueued
        this->_packetsWaiting.release();
        // wake the processing thread
        this->_wait.wakeAll();
    }
}

void PacketDumper::run()
{
    while ( this->_running )
    {
        // wait for a packet
        this->_waitMutex.lock();
        this->_wait.wait(&this->_waitMutex);
        this->_waitMutex.unlock();
        // process all waiting packets
        while ( (this->_packetsWaiting.tryAcquire()) && (this->_running) )
        {
            // getthe packet from the queue
            shared_ptr<RawPacket> rawPacket;
            this->_packetQueue.pop(rawPacket);
            if (rawPacket.get() != 0)
            {
                // extract the packet data
                pcap_pkthdr* head = rawPacket->getHeader().get();
                u_char* packet = rawPacket->getPacket().get();

//                EthernetIIFrame f(rawPacket);
//                mac_t d = f.getDestinationMAC();
//                printf("%02X:%02X:%02X:%02X:%02X:%02X\n", d.U_main.S_uchar.b1, d.U_main.S_uchar.b2, d.U_main.S_uchar.b3, d.U_main.S_uchar.b4, d.U_main.S_uchar.b5, d.U_main.S_uchar.b6 );

                // dump the packet
                pcap_dump( (u_char*)this->_dumpFile, head, packet );
            }
        }
    }
    // write all buffered data to file, and close the dump file
    if ( this->_dumpFile != 0 )
    {
        pcap_dump_flush( this->_dumpFile );
        pcap_dump_close( this->_dumpFile );
        this->_dumpFile = 0;
    }
    if ( this->_dumpInterface != 0 )
    {
        pcap_close( this->_dumpInterface );
        this->_dumpInterface = 0;
    }
}

void PacketDumper::stop()
{
    // stop processing
    this->_running = false;
    this->_wait.wakeAll();
    this->wait();
}

int PacketDumper::waitingPackets()
{
    // return the number of packets waiting to be processed
    return this->_packetsWaiting.available();
}
