#include "abstractionlayer.hh"

#include "alnetworklistener.hh"

AbstractionLayer::AbstractionLayer()
    : NLLListener()
{

}

AbstractionLayer::AbstractionLayer( shared_ptr<ALNetworkListener> nllModule )
    : NLLListener( nllModule )
{

}

AbstractionLayer::AbstractionLayer(
    vector<shared_ptr<ALNetworkListener> > nllModules )
    : NLLListener( nllModules )
{

}

void AbstractionLayer::sendDataLinkLayerPacket( DataLinkLayerPacket& packet,
                              InterfaceRoute& interfaces )
{

}

void AbstractionLayer::sendNetworkLayerPacket( NetworkLayerPacket& packet,
                             InterfaceRoute& interfaces )
{

}

void AbstractionLayer::registerNLL( shared_ptr<ALNetworkListener> nllModule )
{
    vector<shared_ptr<ALNetworkListener> >::const_iterator iter
        = _networkLogicLayer.begin();

    bool exists = false;

    for ( ; iter != _networkLogicLayer.end(), exists == false; iter++ )
    {
        if ( (*iter) == nllModule )
        {
            exists = true;
        }
    }

    if (!exists)
    {
        _networkLogicLayer.push_back(nllModule);
    }
}

void AbstractionLayer::unregisterNLL( shared_ptr<ALNetworkListener> nllModule )
{
    vector<shared_ptr<ALNetworkListener> >::iterator iter
        = _networkLogicLayer.begin();

    bool found = false;

    for ( ; iter != _networkLogicLayer.end(), found == false; iter++ )
    {
        if ( (*iter) == nllModule )
        {
            found = true;
            iter = _networkLogicLayer.erase(iter);
        }
    }
}

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
