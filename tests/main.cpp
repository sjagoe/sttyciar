#define BOOST_TEST_MAIN
#include <boost/test/minimal.hpp>

#include <pcap.h>

#include "rawpacket.hh"
#include "ethernetiiframe.hh"
#include "ipv4datagram.hh"

#define ETHERNETII_MAC_LENGTH 6
#define ETEHRNETII_ETHERTYPE_LENGTH 2

using std::cout;
using std::endl;
using std::vector;

int test_main(int argc, char* argv[])
{

    return 0;
}

void testRawPacket()
{
    const unsigned int numElements = 40;
    u_char* array1 = ( u_char* ) malloc( numElements * sizeof( u_char ) );

    u_char* arr = array1;
    for ( unsigned int i = 0; i < numElements; i++, arr++ )
    {
        *arr = ( i << 4 ) + i;
    }

    arr = array1;

    for ( unsigned int i = 0; i < numElements; i++, arr++ )
    {
        printf("%X ", *arr);
    }
    cout << endl << endl;

    pcap_pkthdr* head = new pcap_pkthdr;
    head->caplen = numElements;
    head->len = numElements;

    RawPacket raw(head, array1);

    free(( void* )array1 );

    delete head;

    vector<u_char> pckt_data = raw.getPacket();

    vector<u_char>::const_iterator iter = pckt_data.begin();
    for (; iter != pckt_data.end(); iter++)
    {
        printf("%X ", *iter);
    }
    cout << endl << endl;

    EthernetIIFrame frame;
    frame.setData(raw);

    array<u_char, ETHERNETII_MAC_LENGTH> sMac = frame.getSourceMAC();
    array<u_char, ETHERNETII_MAC_LENGTH> dMac = frame.getDestinationMAC();
    array<u_char, ETEHRNETII_ETHERTYPE_LENGTH> eType = frame.getEtherType();

    vector<u_char> payload = frame.getPayload();

    cout << "Source MAC: ";
    for (int i = 0; i < (ETHERNETII_MAC_LENGTH-1); i++)
    {
        printf("%X:", sMac[i]);
    }
    printf("%X\n", sMac[ETHERNETII_MAC_LENGTH-1]);

    cout << "Destination MAC: ";
    for (int i = 0; i < (ETHERNETII_MAC_LENGTH-1); i++)
    {
        printf("%X:", dMac[i]);
    }
    printf("%X\n", dMac[ETHERNETII_MAC_LENGTH-1]);

    cout << "EtherType: ";
    for (int i = 0; i < (ETEHRNETII_ETHERTYPE_LENGTH-1); i++)
    {
        printf("%X:", eType[i]);
    }
    printf("%X\n", eType[ETEHRNETII_ETHERTYPE_LENGTH-1]);

    cout << "Payload: ";
    iter = payload.begin();
    for (; iter != payload.end(); iter++)
    {
        printf("%X ", *iter);
    }
    cout << endl << endl;

    raw = frame.getRawPacket();

    vector<u_char> packet = raw.getPacket();
    iter = packet.begin();
    for (; iter != packet.end(); iter++)
    {
        printf("%X ", *iter);
    }
    cout << endl << endl;

    IPv4Datagram datagram(frame);

    cout << "IP Version: " << (int) datagram.getVersion() << " = ";
    printf( "%X", datagram.getVersion() );
    cout << endl;

    cout << "Header Length (in 32-bit Words): "
         << (int) datagram.getHeaderLength() << " = ";
    printf( "%X", datagram.getHeaderLength() );
    cout << endl;

    cout << "Type of Service: " << (int) datagram.getTypeOfService() << " = ";
    printf( "%X", datagram.getTypeOfService() );
    cout << endl;

    cout << "Datagram Length: " << datagram.getDatagramLength() << " = ";
    printf( "%X", datagram.getDatagramLength() );
    cout << endl;

    cout << "Identification: " << datagram.getIdentification() << " = ";
    printf( "%X", datagram.getIdentification() );
    cout << endl;

    cout << "Flags: " << (int) datagram.getFlags() << " = ";
    printf( "%X", datagram.getFlags() );
    cout << endl;

    cout << "Fragmentation Offset: " << datagram.getFragmentationOffset()
        << " = ";
    printf( "%X", datagram.getFragmentationOffset() );
    cout << endl;

    cout << "Flags << 5 | Offset: "
         << ( ( datagram.getFlags() << 13 ) |
         datagram.getFragmentationOffset() )
         << " = ";
    printf( "%X", ( ( datagram.getFlags() << 13 ) |
        datagram.getFragmentationOffset() ) );
    cout << endl;

    cout << "TTL: " << (int) datagram.getTimeToLive() << " = ";
    printf( "%X", datagram.getTimeToLive() );
    cout << endl;

    cout << "Protocol: " << (int) datagram.getProtocol() << " = ";
    printf( "%X", datagram.getProtocol() );
    cout << endl;

    cout << "Checksum: " << datagram.getChecksum() << " = ";
    printf( "%X", datagram.getChecksum() );
    cout << endl;

    array<u_char, 4> source = datagram.getSourceAddress();
    array<u_char, 4> destination = datagram.getDestinationAddress();

    cout << "Source Address: " << (int) source[0] << "." << (int) source[1]
         << "." << (int) source[2] << "." << (int) source[3] << " = ";
    printf( "%X.%X.%X.%X", source[0], source[1], source[2], source[3] );
    cout << endl;

    cout << "Destination Address: " << (int) destination[0] << "."
         << (int) destination[1] << "." << (int) destination[2] << "."
         << (int) destination[3] << " = ";
    printf( "%X.%X.%X.%X", destination[0], destination[1], destination[2],
        destination[3] );
    cout << endl << endl;

    raw = datagram.getRawPacket();


    vector<u_char> packet1 = raw.getPacket();
    iter = packet1.begin();
    for (; iter != packet1.end(); iter++)
    {
        printf("%X ", *iter);
    }
    cout << endl << endl;

}
