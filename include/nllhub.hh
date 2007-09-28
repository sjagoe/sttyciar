#ifndef __NLLHUB_HH__
#define __NLLHUB_HH__

// boost
#include <boost/shared_ptr.hpp>

// Qt
//#include <QPair>

// local
#include "networklogiclayer.hh"

// import from namespaces
using boost::shared_ptr;

// forward declerations
class AbstractionLayer;
class RawPacket;

/*!
Subclass of NetworkLogicLayer providing a basic implementation of a Hub.

\author Simon Jagoe
*/
class NLLHub: public NetworkLogicLayer
{
    public:
        /*!
        Empty constructor to initialise the NetworkLogicLayer
        */
        NLLHub()
            : NetworkLogicLayer()
        {
//            c1 = 0;
//            c2 = 0;
        };

    protected:
        /*!
        Overridden routPacket() method. \see NetworkLogicLayer.

        This provides the logic necessary for a Hub implementation.
        */
        void routePacket( shared_ptr<RawPacket>& packet );

//    private:
//        long long c1;
//        long long c2;
};

#endif
