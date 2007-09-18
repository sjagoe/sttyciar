#include <iostream>

#include "networklogiclayer.hh"
#include "interfaceroute.hh"

bool NetworkLogicLayer::_running;
QMutex NetworkLogicLayer::_runningMutex;

NetworkLogicLayer::NetworkLogicLayer()
{
//    _receiveBuffer.reset( new concurrent_queue<QPair<shared_ptr<RawPacket>,
//                          shared_ptr<InterfaceRoute> > > );
    _receiveBuffer.reset( new LockableQueueGroup<QPair<shared_ptr<RawPacket>,
                          shared_ptr<InterfaceRoute> > > );
}

NetworkLogicLayer::~NetworkLogicLayer()
{
    // remove our references to the shared objects
    _wait.reset();
    _waitingPackets.reset();
    _abstractionLayer.reset();
}

void NetworkLogicLayer::registerAbstractionLayer(
    weak_ptr<AbstractionLayer>& al )
{
    // set the pointer to the abstraction layer
    _abstractionLayer = al;

    // lock the AL as a shared_ptr (prevent it from being destroyed while we
    // are using it
    shared_ptr<AbstractionLayer> lockedAL = getAbstractionLayer();

    // if the AL still exists
    if ( lockedAL.get() )
    {
        // get the devices
        _devices = lockedAL->getDevices();
        // get the WaitCondition for the NLL
        _wait = lockedAL->getNLLWaitCondition();
        // get the Semaphore for the NLL
        _waitingPackets = lockedAL->getNLLSemaphore();
        // enable the NLL
        _runningMutex.lock();
        _running = true;
        _runningMutex.unlock();
    } else {
        // No AL exists, we should throw an exception
    }
}

void NetworkLogicLayer::exitNow()
{
    // prevent the thread loop from running once woken
    _runningMutex.lock();
    _running = false;
    _runningMutex.unlock();
    // wake the thread so that it can run the final loop and exit
    _wait->wakeAll();
}

//void NetworkLogicLayer::packetReceived( shared_ptr<RawPacket>& packet,
//    shared_ptr<Device>& device )
//{
//    shared_ptr<InterfaceRoute> interfaces(new InterfaceRoute( device ) );
//
//    // create QPair and push it onto the queue.
//    _receiveBuffer->push( qMakePair( packet, interfaces ) );
//
//    std::cout << " - Packet Rx: " << device->getName() << endl;
//}

void NetworkLogicLayer::packetReceived()
{
    _waitingPackets->release();
    _wait->wakeAll();
    std::cout << " - Packet Rx: " << endl;
}

void NetworkLogicLayer::registerQueue(
    shared_ptr<LockableQueue<QPair<shared_ptr<RawPacket>,
        shared_ptr<InterfaceRoute> > > > queue )
{
    _receiveBuffer->registerQueue( queue );
}

void NetworkLogicLayer::run()
{
    // loop the thread
    _runningMutex.lock();
    while( _running)
    {
        _runningMutex.unlock();
        // wait for packets when the queue is empty
        _waitMutex.lock();
        _wait->wait( &_waitMutex );
        // once woken up, loop for all packets on the queue
        // if _running becomes false while in this loop, exit.
        _runningMutex.lock();
        while (( _waitingPackets->tryAcquire() ) && (_running) )
        {
            _runningMutex.unlock();
            // pop a packet/interfaceroute QPair from the receive buffer
            QPair<shared_ptr<RawPacket>, shared_ptr<InterfaceRoute> > pair;
            _receiveBuffer->pop( pair );
            // call the method that performs the actual routing
            routePacket( pair.first, pair.second );
            _waitingPackets->tryAcquire();
            _runningMutex.lock();
        }
        _runningMutex.unlock();
        _runningMutex.lock();
    }
    _runningMutex.unlock();
}

shared_ptr<AbstractionLayer> NetworkLogicLayer::getAbstractionLayer()
{
    // obtain a lock on the abstraction layer (i.e. get a shared_ptr with
    // a reference count
    return _abstractionLayer.lock();
}
