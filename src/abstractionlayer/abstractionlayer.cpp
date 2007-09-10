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
