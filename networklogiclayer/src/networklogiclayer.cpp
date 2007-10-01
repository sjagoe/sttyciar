//#include <iostream>

#include "networklogiclayer.hh"
#include "interfaceroute.hh"

bool NetworkLogicLayer::_running;
QMutex NetworkLogicLayer::_runningMutex;

NetworkLogicLayer::NetworkLogicLayer()
{
    this->_receiveBuffer.reset( new LockableQueueGroup<shared_ptr<RawPacket> > );
}

NetworkLogicLayer::~NetworkLogicLayer()
{
    // remove our references to the shared objects
    this->_wait.reset();
    this->_waitingPackets.reset();
    this->_abstractionLayer.reset();
    this->_receiveBuffer.reset();
}

void NetworkLogicLayer::registerAbstractionLayer(
    weak_ptr<AbstractionLayer>& al )
{
    // set the pointer to the abstraction layer
    this->_abstractionLayer = al;

    // lock the AL as a shared_ptr (prevent it from being destroyed while we
    // are using it
    shared_ptr<AbstractionLayer> lockedAL = this->getAbstractionLayer();

    // if the AL still exists
    if ( lockedAL.get() )
    {
        // get the devices
        this->_devices = lockedAL->getActivatedDevices();
//        std::cout << "Number of Activated Devices: " << _devices.size() << std::endl;
        // get the WaitCondition for the NLL
        this->_wait = lockedAL->getNLLWaitCondition();
        // get the Semaphore for the NLL
        this->_waitingPackets = lockedAL->getNLLSemaphore();
        // enable the NLL
        //_runningMutex.lock();
        this->_running = true;
        //_runningMutex.unlock();
    } else {
        // No AL exists, we should throw an exception
    }
}

void NetworkLogicLayer::exitNow()
{
    // prevent the thread loop from running once woken
    //_runningMutex.lock();
    this->_running = false;
    //_runningMutex.unlock();
    // wake the thread so that it can run the final loop and exit
    this->_wait->wakeAll();
    this->wait();
}

void NetworkLogicLayer::packetReceived()
{
    this->_waitingPackets->release();
    this->_wait->wakeAll();
    //std::cout << " - Packet Rx: " << endl;
}

void NetworkLogicLayer::registerQueue(
    shared_ptr<LockableQueue<shared_ptr<RawPacket> > > queue )
{
    this->_receiveBuffer->registerQueue( queue );
}

void NetworkLogicLayer::run()
{
    // loop the thread
    while( this->_running)
    {
        // wait for packets when the queue is empty
        this->_waitMutex.lock();
        this->_wait->wait( &_waitMutex );
        this->_waitMutex.unlock();
        // once woken up, loop for all packets on the queue
        // if _running becomes false while in this loop, exit.
        //while (( _waitingPackets->tryAcquire() ) && (_running) )
        while (( this->_waitingPackets->tryAcquire() ) && (this->_running) )
        {
            // pop a packet/interfaceroute QPair from the receive buffer
            shared_ptr<RawPacket> packet;
            this->_receiveBuffer->pop( packet );
            if (packet.get() != 0)
            {
                // call the method that performs the actual routing
                //routePacket( pair.first, pair.second );
                this->routePacket( packet );
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
    return this->_abstractionLayer.lock();
}

