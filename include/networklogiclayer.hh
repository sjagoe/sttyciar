#ifndef __NLL_BASE_HH__
#define __NLL_BASE_HH__

// Qt includes
#include <QtCore>

// boost includes
#include <boost/weak_ptr.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/scoped_ptr.hpp>

// STL
#include <QList>

// local includes
#include "abstractionlayer.hh"
#include "alnetworklistener.hh"

#include "lockablequeuegroup.hh"

//using tbb::concurrent_queue;

using boost::weak_ptr;
using boost::shared_ptr;
using boost::scoped_ptr;

using std::list;

class RawPacket;

/*!
The NetworkLogicLayer class forms the basis for all NLL modules.

This class manages the threading mechanisms and communication from the
Abstraction Layer and User Interface. A pure virtual method (routePacket)
is provided for the specific NLL module implementation. This method must be
overridden by each specific NLL module implementation to provide the routing
logic of the device being emulated.

\author Simon Jagoe
*/
class NetworkLogicLayer:
    public QThread,
    public ALNetworkListener
{
    Q_OBJECT
    public:
        /*!
        Constructor setting the AbstractionLayer pointer.

        This MUST be called by the inheriting class! This constructor creates
        the LockableQueueGroup used as am incoming packet buffer.
        */
        //NetworkLogicLayer( shared_ptr<AbstractionLayer>& al );
        NetworkLogicLayer();

        /*!
        Virtual destructor, which destroys all the member object pointed to by
        a boost pointer.
        */
        virtual ~NetworkLogicLayer();

        /*!
        Register the AbstractionLayer with the NetworkLogicLayer so that
        packets can be transmitted.

        \param al The AbstractionLayer object to register
        */
        void registerAbstractionLayer( weak_ptr<AbstractionLayer>& al );

        /*!
        A method that allows the thread loops to be stopped

        The NLL will run through one final iteration before stopping, but if
        no packet is ready for routing, it will end immediately.
        */
        void exitNow();

        /*!
        Method provided by the ALNetworkListener for the AL to notify the NLL
        that a packet has been received, and wake the NLL thread.
        */
        void packetReceived();

        /*!
        Overridden method \see ALNetworkListener.
        */
        void
        registerQueue(
            shared_ptr<LockableQueue<shared_ptr<RawPacket> > > queue );

    public slots:
        /*!
        A virtual method that can be overridden to allow timer-based events to
        occur in the NLL.

        \param millisecondsElapsed Time in milliseconds since the last event
        */
        virtual void update( int /*millisecondsElapsed*/ ) {};

    protected:
        //! activated devices used for routing information
        QList<shared_ptr<Device> > _devices;

        /*!
        virtual method provided by QThread, where the actual thread loop is
        implemented.
        */
        void run();

        /*!
        A pure virtual method for specific NLL modules to override and provide
        the routing logic specific to the device.

        \param packet A RawPacket containing the raw packet data and
        InterfaceRoute.
        */
        virtual void routePacket( shared_ptr<RawPacket>& packet ) = 0;

        /*!
        A method to be used by specific NLL module implementations to obtain a
        lock (in the boost::weak_ptr sense) on the abstraction layer.
        */
        shared_ptr<AbstractionLayer> getAbstractionLayer();

    private:
        //! A weak_ptr to the abstraction layer - the weak_ptr prevents cyclic dependencies and memory leaks.
        weak_ptr<AbstractionLayer> _abstractionLayer;

        //! The LockableQueueGroup that the NLL receives packets from
        scoped_ptr<LockableQueueGroup<shared_ptr<RawPacket> > > _receiveBuffer;

        //! the QWaitCondition used to wake up the thread once a packet is on the receive buffer
        shared_ptr<QWaitCondition> _wait;

        //! A QSemaphore to signal how many packets are waiting to be processed
        shared_ptr<QSemaphore> _waitingPackets;

        //! A mutex used by the QWaitCondition
        QMutex _waitMutex;

        //! A static mutex (i.e. shared by all instances of the class) to prevent corrupting of the _running boolean
        static QMutex _runningMutex;

        //! A static bool (shared by all instances of the class) to enable or disable *all* running NLL modules (currently only one instance is supported, but extension is possible. It depends on the AL).
        static bool _running;
};

#endif
