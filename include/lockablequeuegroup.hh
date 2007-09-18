#ifndef __LOCKABLEQUEUEGROUP_HH__
#define __LOCKABLEQUEUEGROUP_HH__

#include <QList>

#include "lockablequeue.hh"

template <class T>
class LockableQueueGroup
{
    public:
        LockableQueueGroup()
        {
            _currentQueue = 0;
        }

        void pop(T& element)
        {
            _queues[_currentQueue]->pop(element);
        };

        void registerQueue(shared_ptr<LockableQueue<T> >& queue)
        {
            _queues.append( queue );
        };

    private:
        unsigned long _currentQueue;
        QList<shared_ptr<LockableQueue<T> > > _queues;
};

#endif
