#include <QWaitCondition>
#include <QSemaphore>
#include <iostream>

#include "abstractionlayer.hh"

#include "alnetworklistener.hh"

#include "rawpacket.hh"

#include "pcapthread.hh"

#include "datalinklayerpacket.hh"

#include "interfaceroute.hh"

AbstractionLayer::AbstractionLayer()
{
    _nllWaitCondition.reset( new QWaitCondition );
    _nllSemaphore.reset( new QSemaphore );
    this->_listening = false;
    this->retrieveDevices();
}

void AbstractionLayer::sendDataLinkLayerPacket(
    shared_ptr<DataLinkLayerPacket>& packet)
{
    //is this inefficient?
    shared_ptr<QList<shared_ptr<Device> > > destinations = packet->getRawPacket()->getInterfaceRoute()->getDestinations();
    for (QList<shared_ptr<Device> >::iterator iter = destinations->begin(); iter != destinations->end(); iter++)
    {
        (*iter)->sendPacket(packet->getRawPacket());

    }
}

void AbstractionLayer::sendNetworkLayerPacket(
    shared_ptr<NetworkLayerPacket>& packet,
    shared_ptr<InterfaceRoute>& interfaces )
{

}

void AbstractionLayer::registerNLL( weak_ptr<ALNetworkListener>& nllModule )
{
    _networkLogicLayer = nllModule;
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
    for(pcap_if* pcapTempDevice=pcapAllDevices; pcapTempDevice != NULL; pcapTempDevice=pcapTempDevice->next)
    {
        tempDevice.reset(new Device(pcapTempDevice));
        this->_devices.push_back(tempDevice);
    }

    pcap_freealldevs(pcapAllDevices);
}

void AbstractionLayer::activateDevice(shared_ptr<Device>& device)
{
    if (!this->isDeviceActivated(device))
        this->_activatedDevices.push_back(device);
}

bool AbstractionLayer::isDeviceActivated(shared_ptr<Device>& device)
{
    for (QList<shared_ptr<Device> >::iterator iter=this->_activatedDevices.begin(); iter!=this->_activatedDevices.end(); ++iter)
        if (**iter==*device)
            return true;
    return false;

}

void AbstractionLayer::startListening(int packetCaptureSize,int timeout)
{
    this->_pcapThreads.clear();
    shared_ptr<PcapThread> tempPcapThread;

    //store the thread objects
    for (QList<shared_ptr<Device> >::iterator iter=this->_activatedDevices.begin(); iter!=this->_activatedDevices.end(); ++iter)
    {
        tempPcapThread.reset(new PcapThread(*iter,packetCaptureSize,timeout,this->_networkLogicLayer));
        this->_pcapThreads.push_back(tempPcapThread);

        (*iter)->startListening();
    }

    //start the thread objects running
    for (QList<shared_ptr<PcapThread> >::iterator iter=this->_pcapThreads.begin(); iter!=this->_pcapThreads.end(); ++iter)
    {
        (*iter)->start();
    }

}

void AbstractionLayer::stopListening()
{
    for (QList<shared_ptr<PcapThread> >::iterator iter=this->_pcapThreads.begin(); iter!=this->_pcapThreads.end(); ++iter)
    {
        (*iter)->stopListening();
        (*iter)->wait();
    }
    this->_pcapThreads.clear();
}

shared_ptr<QWaitCondition>& AbstractionLayer::getNLLWaitCondition()
{
    return _nllWaitCondition;
}

shared_ptr<QSemaphore>& AbstractionLayer::getNLLSemaphore()
{
    return _nllSemaphore;
}
