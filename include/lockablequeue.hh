#ifndef __LOCKABLEQUEUE_HH_
#define __LOCKABLEQUEUE_HH_

#include <QtCore>

template <class T>
class LockableQueue
{
    public:
        LockableQueue(){};

        void push(const T& element)
        {
            _queueMutex.lock();
            _queue.enqueue(element);
            _queueMutex.unlock();
        };

        void pop(T& element)
        {
            _queueMutex.lock();
            element = _queue.dequeue();
            _queueMutex.unlock();
        };

        bool isEmpty()
        {
            return _queue.isEmpty();
        };

    private:
        QQueue<T> _queue;
        QMutex _queueMutex;

//        long long _pushes;
//        long long _pops;
//        QMutex _pushesMutex;
//        QMutex _popsMutex;
};

#endif
