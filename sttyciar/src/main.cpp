#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include "boost/shared_ptr.hpp"
#include <boost/weak_ptr.hpp>

#include "abstractionlayer.hh"
#include "device.hh"
#include "deviceaddress.hh"
#include "address.hh"

#include "nllhub.hh"

int main()
{
    shared_ptr<AbstractionLayer> abstractionLayer( new AbstractionLayer );
    shared_ptr<NetworkLogicLayer> networkLogicLayer( new NLLHub );

    //weak_ptr<AbstractionLayer> weakAL( abstractionLayer );
    weak_ptr<ALNetworkListener> weakNLL( networkLogicLayer );

    abstractionLayer->registerNLL( weakNLL );

    list<shared_ptr<Device> > devices = abstractionLayer->getDevices();

    int count = 0;
    for (list<shared_ptr<Device> >::iterator iter = devices.begin(); iter != devices.end(); ++iter)
    {
        std::cout << count++ << ": "<<(*iter)->getName() << " ["<<(*iter)->getDescription()<<"] "<<std::endl;
        //deviceAddresses = (*iter)->getAddresses();
    }
    std::cout << "choose an adapter: ";

    cin.sync();
    std::string input;
    std::cin >> input;
    std::istringstream iss(input);
    int deviceNo = 0;
    iss >> deviceNo;

    count = 0;
    for (list<shared_ptr<Device> >::iterator iter = devices.begin(); iter != devices.end(); ++iter)
    {
        if (count++==deviceNo)
        {
            abstractionLayer->activateDevice(*iter);
        }
    }
    abstractionLayer->startListening(65535,50);
    std::cout << "Push any button to stop listening...";
    cin.sync();
    char a;
    cin >> a;
    std::cout << "Waiting for threads to die... ";
    abstractionLayer->stopListening();
    std::cout << "Ping! Your waffles are ready!" << endl;

    return 0;
}
