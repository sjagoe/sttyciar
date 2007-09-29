#include "maclookup.hh"

void MACLookup::addEntry( const mac_t& mac, const shared_ptr<Device>& device )
{
    _lookupTable[mac] = qMakePair( device, _aliveTime );
}

shared_ptr<Device> MACLookup::lookupEntry( const mac_t& mac )
{
    return _lookupTable.value( mac ).first;
}

void MACLookup::updateTime(const int& millisecondsElapsed)
{
    QMap<mac_t, QPair<shared_ptr<Device>, long> >::iterator iter = _lookupTable.begin();

    while (iter != _lookupTable.end())
    {
        iter->second = iter->second - millisecondsElapsed;
        if ( iter->second <= 0 )
        {
            iter = _lookupTable.erase(iter);
        }
        else
        {
            iter++;
        }
    }
}
