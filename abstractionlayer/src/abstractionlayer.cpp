#include <QWaitCondition>
#include <QSemaphore>
//#include <iostream>

#include "abstractionlayer.hh"

#include "alnetworklistener.hh"

#include "alstatisticslistener.hh"

#include "rawpacket.hh"

#include "pcapreceivethread.hh"

#include "datalinklayerpacket.hh"

#include "interfaceroute.hh"

#include "defaultstatisticslayer.hh"

AbstractionLayer::AbstractionLayer()
{
    this->_nllWaitCondition.reset( new QWaitCondition );
    this->_nllSemaphore.reset( new QSemaphore );
    this->_statisticsLayer.reset(new DefaultStatisticsLayer());
    this->retrieveDevices();
}

void AbstractionLayer::sendDataLinkLayerPacket(
    shared_ptr<DataLinkLayerPacket> packet)
{
    this->_statisticsLayer->updateStatistics(packet->getRawPacket());

    //is this inefficient?
    shared_ptr<QList<shared_ptr<Device> > > destinations = packet->getRawPacket()->getInterfaceRoute()->getDestinations();
    for (QList<shared_ptr<Device> >::iterator iter = destinations->begin(); iter != destinations->end(); iter++)
    {
        (*iter)->sendPacket(packet->getRawPacket());
    }
}

void AbstractionLayer::sendNetworkLayerPacket(
    shared_ptr<NetworkLayerPacket> /* packet */ ) // uncomment the paramater when implementing the function. It is commented to avoid the annoying warning.
{
}

void AbstractionLayer::registerNLL( weak_ptr<ALNetworkListener>& nllModule )
{
    this->_networkLogicLayer = nllModule;
}

void AbstractionLayer::registerSL(shared_ptr<ALStatisticsListener> slModule)
{
    this->_statisticsLayer = slModule;
}

QList<shared_ptr<Device> > AbstractionLayer::getDevices()
{
    return this->_devices;
}

void AbstractionLayer::retrieveDevices() throw(DeviceNotFoundException)
{
    pcap_if *pcapAllDevices;
    if (pcap_findalldevs(&pcapAllDevices, this->_pcapErrorBuffer) == -1)
        throw DeviceNotFoundException(this->_pcapErrorBuffer);
    shared_ptr<Device> tempDevice;
    weak_ptr<Device> tempDeviceSelf;
    for(pcap_if* pcapTempDevice=pcapAllDevices; pcapTempDevice != NULL; pcapTempDevice=pcapTempDevice->next)
    {
        tempDevice.reset(new Device(pcapTempDevice));
        tempDeviceSelf=tempDevice;
        tempDevice->setSelf(tempDeviceSelf);
        this->_devices.push_back(tempDevice);
    }

    pcap_freealldevs(pcapAllDevices);
}

void AbstractionLayer::activateDevice(shared_ptr<Device>& device)
{
    if (!this->isDeviceActivated(device))
    {
        //std::cout << "AbstractionLayer::activateDevice" << std::endl;
        this->_activatedDevices.push_back(device);
    }
}

void AbstractionLayer::activateDevices( shared_ptr<QStringList> devices )
{
    foreach ( shared_ptr<Device> device, _devices )
    {
        if (devices->contains( QString(device->getName().data()) ) )
        {
            activateDevice( device );
        }
    }
}

bool AbstractionLayer::isDeviceActivated(shared_ptr<Device>& device)
{
    for (QList<shared_ptr<Device> >::iterator iter=this->_activatedDevices.begin(); iter!=this->_activatedDevices.end(); ++iter)
        if (**iter==*device)
            return true;
    return false;

}

QList<shared_ptr<Device> > AbstractionLayer::getActivatedDevices()
{
    return this->_activatedDevices;
}

void AbstractionLayer::startListening(int packetCaptureSize,int timeout)
{
    //this->_pcapThreads.clear();
    //shared_ptr<PcapReceiveThread> tempPcapReceiveThread;

    //store the thread objects
    for (QList<shared_ptr<Device> >::iterator iter=this->_activatedDevices.begin(); iter!=this->_activatedDevices.end(); ++iter)
    {
        (*iter)->startListening(packetCaptureSize,timeout,this->_networkLogicLayer);
        //tempPcapReceiveThread.reset(new PcapReceiveThread(*iter,this->_networkLogicLayer));
        //tempPcapReceiveThread->start();
        //this->_pcapThreads.push_back(tempPcapReceiveThread);
    }

}

void AbstractionLayer::stopListening()
{
    /*for (QList<shared_ptr<PcapReceiveThread> >::iterator iter=this->_pcapThreads.begin(); iter!=this->_pcapThreads.end(); ++iter)
    {
        (*iter)->stopListening();
        (*iter)->wait();
    }
    this->_pcapThreads.clear();*/

    for (QList<shared_ptr<Device> >::iterator iter=this->_activatedDevices.begin(); iter!=this->_activatedDevices.end();iter++)
    {
        (*iter)->stopListening();
    }
}

shared_ptr<QWaitCondition>& AbstractionLayer::getNLLWaitCondition()
{
    return _nllWaitCondition;
}

shared_ptr<QSemaphore>& AbstractionLayer::getNLLSemaphore()
{
    return _nllSemaphore;
}
