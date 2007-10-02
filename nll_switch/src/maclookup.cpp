//#include <iostream>
#include "maclookup.hh"

//void MACLookup::addEntry( const mac_t& mac, const shared_ptr<Device>& device )
//{
////    std::cout << "MACLookup::addEntry" << std::endl;
////    std::cout << sizeof(mac.U_main.S_ushort.high) << " - " << mac.U_main.S_ushort.high << std::endl;
////    std::cout << sizeof(mac.U_main.S_ushort.mid) << " - " << mac.U_main.S_ushort.mid << std::endl;
////    std::cout << sizeof(mac.U_main.S_ushort.low) << " - " << mac.U_main.S_ushort.low << std::endl;
//
//    QMap<u_short, QMap<u_short, QPair<shared_ptr<Device>, long> > > midMap =
//        this->_lookupTable.value( mac.U_main.S_ushort.high );
//    QMap<u_short, QPair<shared_ptr<Device>, long> > innerMap =
//        midMap.value( mac.U_main.S_ushort.mid );
//    innerMap[mac.U_main.S_ushort.low] = qMakePair( device, _aliveTime );
//    midMap[mac.U_main.S_ushort.mid] = innerMap;
//    this->_lookupTable[mac.U_main.S_ushort.high] = midMap;
//}
//
//shared_ptr<Device> MACLookup::lookupEntry( const mac_t& mac )
//{
////    std::cout << "MACLookup::lookupEntry" << std::endl;
////    std::cout << sizeof(mac.U_main.S_ushort.high) << " - " << mac.U_main.S_ushort.high << std::endl;
////    std::cout << sizeof(mac.U_main.S_ushort.mid) << " - " << mac.U_main.S_ushort.mid << std::endl;
////    std::cout << sizeof(mac.U_main.S_ushort.low) << " - " << mac.U_main.S_ushort.low << std::endl;
//
//    QMap<u_short, QMap<u_short, QPair<shared_ptr<Device>, long> > > midMap =
//        this->_lookupTable.value( mac.U_main.S_ushort.high );
//    QMap<u_short, QPair<shared_ptr<Device>, long> > innerMap =
//        midMap.value( mac.U_main.S_ushort.mid );
//    QPair<shared_ptr<Device>, long> contents =
//        innerMap.value( mac.U_main.S_ushort.low );
//    return contents.first;
//}

void MACLookup::updateTime(const int& millisecondsElapsed)
{
//    QMap<u_short, QMap<u_long, QPair<shared_ptr<Device>, long> > >::iterator outIter = this->_lookupTable.begin();
//    while ( outIter != this->_lookupTable.end() )
//    {
//        // extract the innner QMap
//        QMap<u_long, QPair<shared_ptr<Device>, long> > inner = outIter.value();
//
//        // iterate through the QMap
//        QMap<u_long, QPair<shared_ptr<Device>, long> >::iterator inIter = inner.begin();
//        while ( inIter != inner.end() )
//        {
//            // calculate the new lifetime
//            inIter->second = inIter->second - millisecondsElapsed;
//            // if it has expired, erase it
//            if (inIter->second <= 0)
//            {
//                inIter = inner.erase(inIter);
//            }
//            else
//            {
//                inIter++;
//            }
//        }
//
//        // If there are no entries in the inner QMap, erase the key and inner
//        // QMap
//        if (inner.isEmpty())
//        {
//            outIter = this->_lookupTable.erase(outIter);
//        }
//        else
//        {
//            outIter++;
//        }
//    }

//    QMap<mac_t, QPair<shared_ptr<Device>, long> >::iterator iter = _lookupTable.begin();
//
//    while (iter != _lookupTable.end())
//    {
//        iter->second = iter->second - millisecondsElapsed;
//        if ( iter->second <= 0 )
//        {
//            iter = _lookupTable.erase(iter);
//        }
//        else
//        {
//            iter++;
//        }
//    }
}

//void MACLookup::printTable()
//{
//    QMap<u_short, QMap<u_short, QMap<u_short, QPair<shared_ptr<Device>, long> > > >::iterator outIter = this->_lookupTable.begin();
//    while ( outIter != this->_lookupTable.end() )
//    {
//        std::cout << "+ " << outIter.key() << std::endl;
//        // extract the innner QMap
//        QMap<u_short, QMap<u_short, QPair<shared_ptr<Device>, long> > > mid = outIter.value();
//        QMap<u_short, QMap<u_short, QPair<shared_ptr<Device>, long> > >::iterator midIter = mid.begin();
//
//        while ( midIter != mid.end() )
//        {
//            std::cout << "+ -- " << midIter.key() << std::endl;
//            QMap<u_short, QPair<shared_ptr<Device>, long> > inner = midIter.value();
//
//            // iterate through the inner QMap
//            QMap<u_short, QPair<shared_ptr<Device>, long> >::iterator inIter = inner.begin();
//            while ( inIter != inner.end() )
//            {
//                std::cout << "+ -- -- " << inIter.key() << std::endl;
//                inIter++;
//            }
//            midIter++;
//        }
//        outIter++;
//    }
//}
