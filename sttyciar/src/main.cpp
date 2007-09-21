//#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <pcap.h>
#include "boost/shared_ptr.hpp"
#include <boost/weak_ptr.hpp>
#include "abstractionlayer.hh"
#include "device.hh"
#include "deviceaddress.hh"
#include "address.hh"

#include "nllhub.hh"

#include "ethernetiiframe.hh"

/*
    0                   1                   2                   3
    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |Version|  IHL  |Type of Service|          Total Length         |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |         Identification        |Flags|      Fragment Offset    |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |  Time to Live |    Protocol   |         Header Checksum       |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |                       Source Address                          |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |                    Destination Address                        |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |                    Options                    |    Padding    |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
*/

const u_char pingPacketData[] =
{
    // MAC Header
    0x00, 0x50, 0xbf, 0xec, 0x7b, 0x2b, // destination MAC// simon-laptop-wired
    0x01, 0x13, 0xa9, 0x09, 0xdd, 0xce, // source MAC
    0x08, 0x00, // ethertype (IP)
    // IPv4 header
    0x45, // version (0x4) | header length (0x5)
    0x00, // Type of Service
    0x00, 0x54, // Total Length
    0x00, 0x00, // Identification
    0x40, 0x00, // flags (0x2) | offset (0x0000)
    0x40, // TTL
    0x01, // Protocol (ICMP - 0x01)
//    0x41, 0xa5, // header checksum ( 0xb9 0x43 )
//    0x92, 0x8d, 0x6e, 0x2a, // source IP address // 146.141.110.42
//    0x40, 0xe9, 0xb7, 0x63, // destination IP address  // 64.233.183.99
//    0xb9, 0x43, // new checksum
//    0xc0, 0xa8, 0x00, 0x0a, // new source IP // 192.168.0.10 (0xc0 0xa8 0x00 0x0a)
//    0xc0, 0xa8, 0x00, 0x0b, // new dest IP // 192.168.0.11 (0xc0 0xa8 0x00 0x0b)
    0x19, 0x53, // new checksum
    0xc0, 0xa8, 0x50, 0x04,// new source IP // 192.168.80.4 (0xc0 0xa8 0x50 0x04)
    0xc0, 0xa8, 0x50, 0x01,// new destination IP // 192.168.80.1 (0xc0 0xa8 0x50 0x01) 34
    // ICMP
    0x08, // type 8 (echo request)
    0x00, // code 0
    0xb1, 0x8f, // checksum
    0x6f, 0x19, // identifier
    0x00, 0x0c, // sequence number 42
    // ICMP Data
    0x86, 0x26, 0xf2, 0x46, 0x71, 0xda, 0x02, 0x00, 0x08, 0x09, 0x0a, 0x0b,
    0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
    0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f, 0x20, 0x21, 0x22, 0x23,
    0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f, // 90
    0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37 //98
};

const int size = 98;

int main()
{
    shared_ptr<AbstractionLayer> abstractionLayer( new AbstractionLayer );
    shared_ptr<NetworkLogicLayer> networkLogicLayer( new NLLHub );

    weak_ptr<AbstractionLayer> weakAL( abstractionLayer );
    weak_ptr<ALNetworkListener> weakNLL( networkLogicLayer );

    abstractionLayer->registerNLL( weakNLL );
    networkLogicLayer->registerAbstractionLayer( weakAL );

    QList<shared_ptr<Device> > devices = abstractionLayer->getDevices();

    int count = 0;
    for (QList<shared_ptr<Device> >::iterator iter = devices.begin(); iter != devices.end(); ++iter)
    {
        std::cout << count++ << ": "<<(*iter)->getName() << " ["<<(*iter)->getDescription()<<"] "<<std::endl;
        //deviceAddresses = (*iter)->getAddresses();
    }
    std::cout << "choose an adapter: ";
    cout.flush();
    cin.sync();
    std::string input;
    std::cin >> input;
    std::istringstream iss(input);
    int deviceNo = 0;
    iss >> deviceNo;
    shared_ptr<Device> dev;
    count = 0;
    for (QList<shared_ptr<Device> >::iterator iter = devices.begin(); iter != devices.end(); ++iter)
    {
        if (count++==deviceNo)
        {
            dev = *iter;
            abstractionLayer->activateDevice(*iter);
        }
    }

    abstractionLayer->startListening(65535,50);
    networkLogicLayer->start();

    u_char* data = new u_char[size];
    *data = *pingPacketData;

    for (int i = 0; i != size; i++)
    {
        //printf("%2X\n", pingPacketData[i]);
        data[i] = pingPacketData[i];
    }

    shared_ptr<RawPacket> raw( new RawPacket );
    raw->setPacket( data, size );

    shared_ptr<DataLinkLayerPacket> dllp( new EthernetIIFrame( raw ) );
    dllp->addDestination(dev);

    for (int flood = 0; flood < 10; flood++)
    {
        abstractionLayer->sendDataLinkLayerPacket(dllp);
    }

    std::cout << "Push any button to stop listening...";
    cout.flush();
    cin.sync();
    char a;
    cin >> a;
    cout << "Waiting for threads to die... " << endl;
    abstractionLayer->stopListening();
    networkLogicLayer->exitNow();
    networkLogicLayer->wait();
    std::cout << "Ping! Your waffles are ready!" << endl;

//    shared_ptr<AbstractionLayer> abstractionLayer( new AbstractionLayer );
//    shared_ptr<NetworkLogicLayer> networkLogicLayer( new NLLHub );
//
//    weak_ptr<AbstractionLayer> weakAL( abstractionLayer );
//    weak_ptr<ALNetworkListener> weakNLL( networkLogicLayer );
//
//    abstractionLayer->registerNLL( weakNLL );
//    networkLogicLayer->registerAbstractionLayer( weakAL );
//
//    QList<shared_ptr<Device> > devices = abstractionLayer->getDevices();
//
//    int count = 0;
//    for (QList<shared_ptr<Device> >::iterator iter = devices.begin(); iter != devices.end(); ++iter)
//    {
//        std::cout << count++ << ": "<<(*iter)->getName() << " ["<<(*iter)->getDescription()<<"] "<<std::endl;
//        //deviceAddresses = (*iter)->getAddresses();
//    }
//    std::cout << "choose an adapter: ";
//
//    cin.sync();
//    std::string input;
//    std::cin >> input;
//    std::istringstream iss(input);
//    int deviceNo = 0;
//    iss >> deviceNo;
//
//    count = 0;
//    for (QList<shared_ptr<Device> >::iterator iter = devices.begin(); iter != devices.end(); ++iter)
//    {
//        if (count++==deviceNo)
//        {
//            abstractionLayer->activateDevice(*iter);
//        }
//    }
//    abstractionLayer->startListening(65535,50);
//    networkLogicLayer->start();
//    std::cout << "Push any button to stop listening...";
//    cin.sync();
//    char a;
//    cin >> a;
//    std::cout << "Waiting for threads to die... ";
//    abstractionLayer->stopListening();
//    networkLogicLayer->exitNow();
//    networkLogicLayer->wait();
//    std::cout << "Ping! Your waffles are ready!" << endl;
//
//    return 0;
}
