#include <QWaitCondition>
#include <QSemaphore>

#include "abstractionlayer.hh"

#include "alnetworklistener.hh"

#include "rawpacket.hh"

AbstractionLayer::AbstractionLayer()
{
    _nllWaitCondition.reset( new QWaitCondition );
    _nllSemaphore.reset( new QSemaphore );
}

//AbstractionLayer::AbstractionLayer( shared_ptr<ALNetworkListener> nllModule )
//{
//    AbstractionLayer();
//    //_networkLogicLayer.push_back( nllModule );
//    _networkLogicLayer = nllModule;
//}

//AbstractionLayer::AbstractionLayer(
//    vector<shared_ptr<ALNetworkListener> > nllModules )
//{
//    AbstractionLayer();
//    _networkLogicLayer.resize( nllModules.size() );
//    std::copy( nllModules.begin(), nllModules.end(),
//               _networkLogicLayer.begin() );
//}

void AbstractionLayer::sendDataLinkLayerPacket(
    shared_ptr<DataLinkLayerPacket>& packet,
    shared_ptr<InterfaceRoute>& interfaces )
{

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

list<shared_ptr<Device> > AbstractionLayer::getDevices() throw(DeviceNotFoundException)
{
    pcap_if *pcapAllDevices;

    if (pcap_findalldevs(&pcapAllDevices, this->_pcapErrorBuffer) == -1)
        throw DeviceNotFoundException(this->_pcapErrorBuffer);
    list<shared_ptr<Device> > devices;
    shared_ptr<Device> tempDevice;
    for(pcap_if* pcapTempDevice=pcapAllDevices; pcapTempDevice != NULL; pcapTempDevice=pcapTempDevice->next)
    {
        tempDevice.reset(new Device(pcapTempDevice));
        devices.push_back(tempDevice);
    }

    pcap_freealldevs(pcapAllDevices);
    return devices;


}

void AbstractionLayer::activateDevice(shared_ptr<Device>& device)
{
    if (!this->isDeviceActivated(device))
        this->_activatedDevices.push_back(device);
}

bool AbstractionLayer::isDeviceActivated(shared_ptr<Device>& device)
{
    for (list<shared_ptr<Device> >::iterator iter=this->_activatedDevices.begin(); iter!=this->_activatedDevices.end(); ++iter)
        if (**iter==*device)
            return true;
    return false;

}

//void AbstractionLayer::startListening()
//{
//
//}

shared_ptr<QWaitCondition>& AbstractionLayer::getNLLWaitCondition()
{
    return _nllWaitCondition;
}

shared_ptr<QSemaphore>& AbstractionLayer::getNLLSemaphore()
{
    return _nllSemaphore;
}
