//#include <iostream>

#include "networklogiclayer.hh"
#include "interfaceroute.hh"

bool NetworkLogicLayer::_running;
QMutex NetworkLogicLayer::_runningMutex;

NetworkLogicLayer::NetworkLogicLayer()
{
    _receiveBuffer.reset( new LockableQueueGroup<shared_ptr<RawPacket> > );
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
        _devices = lockedAL->getActivateDevices();
//        std::cout << "Number of Activated Devices: " << _devices.size() << std::endl;
        // get the WaitCondition for the NLL
        _wait = lockedAL->getNLLWaitCondition();
        // get the Semaphore for the NLL
        _waitingPackets = lockedAL->getNLLSemaphore();
        // enable the NLL
        //_runningMutex.lock();
        _running = true;
        //_runningMutex.unlock();
    } else {
        // No AL exists, we should throw an exception
    }
}

void NetworkLogicLayer::exitNow()
{
    // prevent the thread loop from running once woken
    //_runningMutex.lock();
    _running = false;
    //_runningMutex.unlock();
    // wake the thread so that it can run the final loop and exit
    _wait->wakeAll();
}

void NetworkLogicLayer::packetReceived()
{
    _waitingPackets->release();
    _wait->wakeAll();
    //std::cout << " - Packet Rx: " << endl;
}

void NetworkLogicLayer::registerQueue(
    shared_ptr<LockableQueue<shared_ptr<RawPacket> > > queue )
{
    _receiveBuffer->registerQueue( queue );
}

void NetworkLogicLayer::run()
{
    // loop the thread
    while( _running)
    {
        // wait for packets when the queue is empty
        _waitMutex.lock();
        _wait->wait( &_waitMutex );
        _waitMutex.unlock();
        // once woken up, loop for all packets on the queue
        // if _running becomes false while in this loop, exit.
        //while (( _waitingPackets->tryAcquire() ) && (_running) )
        while (( _waitingPackets->tryAcquire() ) && (_running) )
        {
            // pop a packet/interfaceroute QPair from the receive buffer
            shared_ptr<RawPacket> packet;
            _receiveBuffer->pop( packet );
            if (packet.get() != 0)
            {
                // call the method that performs the actual routing
                //routePacket( pair.first, pair.second );
                routePacket( packet );
            }
//            else
//            {
//                std::cout << "Null pointer in NLL::run()" << std::endl;
//            }
        }
    }
}

shared_ptr<AbstractionLayer> NetworkLogicLayer::getAbstractionLayer()
{
    // obtain a lock on the abstraction layer (i.e. get a shared_ptr with
    // a reference count
    return _abstractionLayer.lock();
}

