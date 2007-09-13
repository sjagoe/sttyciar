#include "networklogiclayer.hh"

bool NetworkLogicLayer::_running;
QMutex NetworkLogicLayer::_runningMutex;

void NetworkLogicLayer::exitNow()
{
    // prevent the thread loop from running once woken
    _runningMutex.lock();
    _running = false;
    _runningMutex.unlock();
    // wake the thread so that it can run the final loop and exit
    _wait->wakeAll();
}

void NetworkLogicLayer::packetReceived( RawPacket& packet,
    InterfaceRoute& interfaces )
{
    // create a QPair and push it onto the concurrent_queue
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
            // pop a packet/interfaceroute QPair from the concurrent_queue
            shared_ptr<RawPacket> raw;
            shared_ptr<InterfaceRoute> ifaces;
            // call the method that performs the actual routing
            routePacket(raw, ifaces);
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
