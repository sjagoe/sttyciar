#ifndef __LOCKABLEQUEUE_HH_
#define __LOCKABLEQUEUE_HH_

#include <QtCore>

/*!
LockableQueue provides a threadsafe interface to a QQueue (through the use of
the QMutex class). Any queue operation is preceded by a QMutex.lock(), and
followed by a QMutex.unlock().

\author Simon Jagoe
*/
template <class T>
class LockableQueue
{
    public:
        /*!
        Empty constructor.
        */
        LockableQueue(){};

        /*!
        Enqueue an element onto the QQueue.

        The method was named push() for compatibility with the tbb::concurrent_queue.

        \param element The element to enqueue.
        */
        void push(const T& element)
        {
            _queueMutex.lock();
            _queue.enqueue(element);
            _queueMutex.unlock();
        };

        /*!
        Dequeue an element from the queue.

        The method was named pop() for compatibility with the tbb::concurrent_queue.

        \param element The dequeued element is returned in the paramater (again for compatibility with tbb::concurrent_queue).
        */
        void pop(T& element)
        {
            _queueMutex.lock();
            if (!_queue.isEmpty())
                element = _queue.dequeue();
            _queueMutex.unlock();
        };

        /*!
        Check if the queue is empty.

        \return true if the queue is empty, false otherwise. See QQueue Documentation
        */
        bool isEmpty()
        {
            return _queue.isEmpty();
        };

    private:
        //! QQueue instance to form the basis of the LockableQueue.
        QQueue<T> _queue;

        //! QMutex used to lock the QQueue.
        QMutex _queueMutex;


//        long long _pushes;
//        long long _pops;
//        QMutex _pushesMutex;
//        QMutex _popsMutex;
};

#endif
