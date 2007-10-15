#ifndef __LOCKABLEQUEUEGROUP_HH__
#define __LOCKABLEQUEUEGROUP_HH__

#include <QList>

#include "lockablequeue.hh"

/*!
LockableQueueGroup allows each PcapReceiveThread to enqueue to a different queue
and the NLL to dequeue from all of them transparently.

This prevents the receiving threads from blocking each other, allowing more
efficiency. Receiving threads only block the NLL, and the NLL only blocks the
thread whose queue is being dequeue from.

\author Simon Jagoe
*/
template <class T>
class LockableQueueGroup
{
    public:
        /*!
        Initialise members.
        */
        LockableQueueGroup()
        {
            _currentQueue = 0;
        }

        /*!
        Dequeue an element.

        This method is compatible with the tbb::concurrent_queue.pop() method.

        \param element variable that will contain the dequeued element.
        */
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

        /*!
        Register a LockableQueue with the LockableQueueGroup so that elements
        may be dequeued from it.

        \param queue The queue to register
        */
        void registerQueue(shared_ptr<LockableQueue<T> >& queue)
        {
            _queues.append( queue );
        };

    private:

        //! The index of the currently active queue (where the next dequeue will occur).
        long _currentQueue;

        //! List of queues accessible by the LockableQueueGroup
        QList<shared_ptr<LockableQueue<T> > > _queues;
};

#endif
