#include <iostream>

#include <pcap.h>

#include "packet.hh"
#include "ethernetiiframe.hh"

using std::cout;
using std::endl;
using std::vector;

int main()
{

    u_char* array1 = ( u_char* ) malloc( 16 * sizeof( u_char ) );

    //u_char array[16] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF};
    u_char* arr = array1;
    for ( int i = 0; i < 16; i++, arr++ )
    {
        *arr = ( i << 4 ) + i;
    }

    arr = array1;

    for ( int i = 0; i < 16; i++, arr++ )
    {
        cout << ( unsigned int ) *arr << endl;
    }
    cout << endl;

    pcap_pkthdr* head = new pcap_pkthdr;
    head->caplen = 16;
    head->len = 16;

    Packet a(head, array1);

    free(( void* )array1 );

    delete head;

    vector<u_char> pckt_data = a.getPacket();

    vector<u_char>::const_iterator iter = pckt_data.begin();
    for (; iter != pckt_data.end(); iter++)
    {
        cout << (unsigned int) *iter << endl;
    }
    cout << endl;

    EthernetIIFrame b(a);

    array<u_char, ETHERNETII_MAC_LENGTH> s = b.getSourceMAC();
    array<u_char, ETHERNETII_MAC_LENGTH> d = b.getDestinationMAC();
    array<u_char, ETEHRNETII_ETHERTYPE_LENGTH> e = b.getEtherType();

    vector<u_char> p = b.getPayload();

    cout << "Source MAC: ";
    for (int i = 0; i < (ETHERNETII_MAC_LENGTH-1); i++)
    {
        printf("%X:", s[i]);
    }
    printf("%X\n", s[ETHERNETII_MAC_LENGTH-1]);

    cout << "Destination MAC: ";
    for (int i = 0; i < (ETHERNETII_MAC_LENGTH-1); i++)
    {
        printf("%X:", d[i]);
    }
    printf("%X\n", d[ETHERNETII_MAC_LENGTH-1]);

    cout << "EtherType: ";
    for (int i = 0; i < (ETEHRNETII_ETHERTYPE_LENGTH-1); i++)
    {
        printf("%X:", e[i]);
    }
    printf("%X\n", e[ETEHRNETII_ETHERTYPE_LENGTH-1]);

    cout << "Payload: ";
    iter = p.begin();
    for (; iter != p.end(); iter++)
    {
        printf("%X ", *iter);
    }
    cout << endl << endl;


    return 0;
}
