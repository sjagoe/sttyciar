#ifndef __LOCKABLEQUEUEGROUP_HH__
#define __LOCKABLEQUEUEGROUP_HH__

#include "lockablequeue.hh"

template <class T>
class LockableQueueGroup
{
    public:
        LockableQueueGroup();

        //void

    private:
        unsigned long _totalQueues;
        unsigned long _currentQueue;
        LockableQueue<T> _queue;
};

#endif
