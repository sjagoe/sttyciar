#include <iostream>
#include <list>
#include "abstractionlayer.hh"
#include "device.hh"
#include "exceptions.hh"

using boost::array;

using namespace std;

int main(int argc,char* argv[])
{
    AbstractionLayer* al = new AbstractionLayer();

    list<Device> devices;
    try
    {
        devices = al->getDevices();
    }
    catch (DeviceNotFoundException& dnfe)
    {
        cerr << dnfe.what();
    }

    int i = 1;
    for (list<Device>::const_iterator it = devices.begin(); it!=devices.end(); ++it)
    {
        cout << "Device " << i++ << endl;
        cout << "--------"<<endl;
        cout << "  Name: " << it->getName() << endl;
        cout << "  Description: " << it->getDescription() << endl;
        cout << "  Is loopback: " << ((it->isLoopback())?"Yes":"No") << endl;

        Address address;
        int j=1;
        for (list<DeviceAddress>::const_iterator it2 = it->getAddresses().begin(); it2!=it->getAddresses().end(); ++it2,j++)
        {
            cout << "  Address " << j << ": " << endl;

            cout << "     ";
            address=it2->getAddress();
            cout << "IP address: ";
            cout << (unsigned int) address.getAddressByte(0)<<".";
            cout << (unsigned int) address.getAddressByte(1)<<".";
            cout << (unsigned int) address.getAddressByte(2)<<".";
            cout << (unsigned int) address.getAddressByte(3)<<endl;

            cout << "     ";
            address=it2->getNetmask();
            cout << "Netmask: ";
            cout << (unsigned int) address.getAddressByte(0)<<".";
            cout << (unsigned int) address.getAddressByte(1)<<".";
            cout << (unsigned int) address.getAddressByte(2)<<".";
            cout << (unsigned int) address.getAddressByte(3)<<endl;

            cout << "     ";
            address=it2->getBroadcastAddress();
            cout << "Broadcast address: ";
            cout << (unsigned int) address.getAddressByte(0)<<".";
            cout << (unsigned int) address.getAddressByte(1)<<".";
            cout << (unsigned int) address.getAddressByte(2)<<".";
            cout << (unsigned int) address.getAddressByte(3)<<endl;

            cout << "     ";
            address=it2->getDestinationAddress();
            cout << "Destination address: ";
            cout << (unsigned int) address.getAddressByte(0)<<".";
            cout << (unsigned int) address.getAddressByte(1)<<".";
            cout << (unsigned int) address.getAddressByte(2)<<".";
            cout << (unsigned int) address.getAddressByte(3)<<endl;
        }

        cout << endl;
    }

    delete al;
    return 0;
}
