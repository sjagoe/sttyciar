#ifndef __NLLHUB_HH__
#define __NLLHUB_HH__

// boost
#include <boost/shared_ptr.hpp>

// Qt
#include <QPair>

// local
#include "networklogiclayer.hh"

// import from namespaces
using boost::shared_ptr;

// forward declerations
class AbstractionLayer;

class NLLHub: public NetworkLogicLayer
{
    public:
        NLLHub( shared_ptr<AbstractionLayer>& al )
            : NetworkLogicLayer( al )
        {}

    protected:
        void routePacket( QPair<shared_ptr<RawPacket>,
            shared_ptr<InterfaceRoute> >& packet );
};

#endif
