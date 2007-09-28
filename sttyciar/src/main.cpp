#include <QApplication>
#include "sttyciarrunner.hh"
//#include <iostream>
//#include "statisticslayer.hh"
//#include "abstractionlayer.hh"

//#include <vector>
//#include <iostream>
//#include <sstream>
//#include <string>
//#include "boost/shared_ptr.hpp"
//#include <boost/weak_ptr.hpp>
//
//#include "abstractionlayer.hh
//#include "device.hh"
//#include "deviceaddress.hh"
//#include "address.hh"
//
//#include "nllhub.hh"

int main(int argc, char* argv[])
{
    // Actual main
    QApplication app(argc, argv);
    SttyciarRunner runner;
    QObject::connect(&runner, SIGNAL(exit()), &app, SLOT(quit()));
    return app.exec();

// testing stuff goes here is you comment out the actual main!

//    StatisticsLayer sl;
//    AbstractionLayer al;
//    QList<shared_ptr<Device> > devices = al.getDevices();
//    sl.initializeTable(devices);
//
//    for (QList<shared_ptr<Device > >::iterator iter = devices.begin(); iter != devices.end(); iter++)
//    {
//        std::cout << (*iter)->getName() << std::endl;
//    }
//    std::cout << std::endl;
//
//    InterfaceRoute ir;
//    ir.setSource(devices[0]);
//    ir.addDestination(devices[1]);
//    ir.addDestination(devices[2]);
//    sl.updateStatistics(ir);
//
//    ir.clearDestinations();
//    ir.setSource(devices[1]);
//    ir.addDestination(devices[2]);
//    ir.addDestination(devices[0]);
//    sl.updateStatistics(ir);
//
//
//    std::cout << sl.toString();





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
