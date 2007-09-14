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

AbstractionLayer::AbstractionLayer( shared_ptr<ALNetworkListener> nllModule )
{
    AbstractionLayer();
    //_networkLogicLayer.push_back( nllModule );
    _networkLogicLayer = nllModule;
}

//AbstractionLayer::AbstractionLayer(
//    vector<shared_ptr<ALNetworkListener> > nllModules )
//{
//    AbstractionLayer();
//    _networkLogicLayer.resize( nllModules.size() );
//    std::copy( nllModules.begin(), nllModules.end(),
//               _networkLogicLayer.begin() );
//}

void AbstractionLayer::sendDataLinkLayerPacket( DataLinkLayerPacket& packet,
                              InterfaceRoute& interfaces )
{

}

void AbstractionLayer::sendNetworkLayerPacket( NetworkLayerPacket& packet,
                             InterfaceRoute& interfaces )
{

}

void AbstractionLayer::registerNLL( ALNetworkListener* nllModule )
{
    _networkLogicLayer.reset( nllModule );

//    vector<shared_ptr<ALNetworkListener> >::const_iterator iter
//        = _networkLogicLayer.begin();
//
//    bool exists = false;
//
//    for ( ; iter != _networkLogicLayer.end(), exists == false; iter++ )
//    {
//        if ( (*iter) == nllModule )
//        {
//            exists = true;
//        }
//    }
//
//    if (!exists)
//    {
//        _networkLogicLayer.push_back(nllModule);
//    }
}

//void AbstractionLayer::unregisterNLL( shared_ptr<ALNetworkListener>& nllModule )
//{
//    vector<shared_ptr<ALNetworkListener> >::iterator iter
//        = _networkLogicLayer.begin();
//
//    bool found = false;
//
//    for ( ; iter != _networkLogicLayer.end(), found == false; iter++ )
//    {
//        if ( (*iter) == nllModule )
//        {
//            found = true;
//            iter = _networkLogicLayer.erase(iter);
//        }
//    }
//}

list<Device> AbstractionLayer::getDevices() throw(DeviceNotFoundException)
{
    pcap_if *pcapAllDevices;

    if (pcap_findalldevs(&pcapAllDevices, this->pcapErrorBuffer) == -1)
        throw DeviceNotFoundException(this->pcapErrorBuffer);
    list<Device> devices;
    Device tempDevice;
    for(pcap_if* pcapTempDevice=pcapAllDevices; pcapTempDevice != NULL; pcapTempDevice=pcapTempDevice->next)
    {
        tempDevice.setContents(pcapTempDevice);
        devices.push_back(tempDevice);
    }

    pcap_freealldevs(pcapAllDevices);
    return devices;


}

void AbstractionLayer::activateDevice(Device device)
{

}

bool AbstractionLayer::isDeviceActivated(Device device)
{
    for (list<Device>::iterator iter=this->activatedDeviceNames.begin(); iter!=this->activatedDeviceNames.end(); ++iter)
        if (iter->getName() == device.getName())
            return true;
    return false;

}
void AbstractionLayer::startListening()
{
}

shared_ptr<QWaitCondition>& AbstractionLayer::getNLLWaitCondition()
{
    return _nllWaitCondition;
}



shared_ptr<QSemaphore>& AbstractionLayer::getNLLSemaphore()
{
    return _nllSemaphore;
}
