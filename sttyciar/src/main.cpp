#include <list>
#include <iostream>
#include "boost/shared_ptr.hpp"
#include "abstractionlayer.hh"
#include "device.hh"
#include "deviceaddress.hh"
#include "address.hh"

int main()
{
    AbstractionLayer a;
    list<shared_ptr<Device> > devices=a.getDevices();
    list<DeviceAddress> deviceAddresses;

    for (list<shared_ptr<Device> >::iterator iter = devices.begin(); iter != devices.end(); ++iter)
    {
        std::cout << (*iter)->getName() << std::endl;
        deviceAddresses = (*iter)->getAddresses();
        for (list<DeviceAddress>::iterator iter2 = deviceAddresses.begin(); iter2 != deviceAddresses.end(); ++iter2)
        {
            Address address = iter2->getAddress();
            std::cout<<address.toIPString();
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
    return 0;
}
