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
            if (++_currentQueue >= _queues.size())
            {
                _currentQueue = 0;
            }
        };

        void registerQueue(shared_ptr<LockableQueue<T> >& queue)
        {
            _queues.append( queue );
        };

    private:
        long _currentQueue;
        QList<shared_ptr<LockableQueue<T> > > _queues;
};

#endif
