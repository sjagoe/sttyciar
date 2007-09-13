#ifndef __NLL_BASE_HH__
#define __NLL_BASE_HH__

#include <QtCore>

#include <boost/weak_ptr.hpp>
#include <boost/shared_ptr.hpp>

#include "abstractionlayer.hh"
#include "alnetworklistener.hh"

using boost::weak_ptr;
using boost::shared_ptr;

class RawPacket;

class NetworkLogicLayer: public QThread, public ALNetworkListener
{
    Q_OBJECT
    public:
        NetworkLogicLayer( shared_ptr<AbstractionLayer>& al )
            : ALNetworkListener( al )
        {
            //_abstractionLayer = al;
            shared_ptr<AbstractionLayer> lockedAL = _abstractionLayer.lock();
            _wait = lockedAL->getNLLWaitCondition();
            _waitingPackets = lockedAL->getNLLSemaphore();
            _running = true;
        };

        virtual ~NetworkLogicLayer()
        {
            _wait.reset();
            _waitingPackets.reset();
        };

        void exitNow();

        void packetReceived( RawPacket& packet, InterfaceRoute& interfaces );

    protected:
        void run();
        virtual void routePacket( shared_ptr<RawPacket>& packet,
            shared_ptr<InterfaceRoute>& interfaces) = 0;

        inline shared_ptr<AbstractionLayer> getAbstractionLayer();

    private:
        shared_ptr<QWaitCondition> _wait;
        shared_ptr<QSemaphore> _waitingPackets;
        QMutex _waitMutex;
        static QMutex _runningMutex;
        static bool _running;
};

#endif
