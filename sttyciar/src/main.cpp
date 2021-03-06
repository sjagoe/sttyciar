#include <QApplication>
#include "sttyciarrunner.hh"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    SttyciarRunner runner;
    QObject::connect(&runner, SIGNAL(exit()), &app, SLOT(quit()));
    QObject::connect(&app, SIGNAL( lastWindowClosed() ), &runner, SLOT( exitSttyciar() ) );
    return app.exec();
}

//#include <iostream>
//#include "statisticslayer.hh"
//#include "abstractionlayer.hh"
//#include "statistics.hh"

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

//int main(int argc, char* argv[])
//{
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
//    //sl.updateStatistics(ir);
//
//
//    std::cout << sl.toString();
//
//    shared_ptr<Statistics> stats(sl.getStatistics());
//    std::cout << "total packets: " << stats->getTotalPackets() << endl;
//    std::cout << "Percentages: \n";
//    for (int i = 0 ; i < 3; i++)
//    {
//        for (int j = 0; j < 3; j++)
//        {
//            if (i!=j)
//            {
//
//                std::cout << stats->getTrafficPercentage(devices[i],devices[j]) << " ";
//            }
//        }
//        std::cout << std::endl;
//    }



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
//}

/*int main(int argc, char* argv[])
{
    uint8_t address[] = {255,255,255,0};
    Address a(address,4);
    cout << a.to_bpf_u_int32();
}*/
/*#include <iostream>
//#include <List>
#include <QList>

using namespace std;

int main()
{
    QList<int> mylist;
    mylist.push_back(3);
    mylist.push_back(3);
    mylist.push_back(3);
    mylist.push_back(1);
    mylist.push_back(2);
    mylist.push_back(3);
    mylist.push_back(3);
    mylist.push_back(4);
    mylist.push_back(5);
    mylist.push_back(3);
    mylist.push_back(2);
    mylist.push_back(3);
    mylist.push_back(3);

    QList<int>::iterator i = mylist.begin();
    while (i != mylist.end())
    {
        if (*i == 3)
        {
            i=mylist.erase(i);
        }
        else
        {
            i++;
        }
    }
    / *for (QList<int>::iterator i = mylist.begin(); i != mylist.end(); i++)
    {
        if (*i == 3)
        {
            i=mylist.erase(i);
        }
    }*/

/*    for (QList<int>::iterator i = mylist.begin(); i != mylist.end(); i++)
    {
        std::cout << *i;
    }
}*/


