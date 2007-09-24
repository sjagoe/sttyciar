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
            int temp = _currentQueue;
            do
            {
                {
                    _queues[_currentQueue]->pop(element);
                }
                _currentQueue = (_currentQueue + 1) % _queues.size();
            }
            while ((_currentQueue != temp));
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
