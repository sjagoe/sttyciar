#ifndef __WINDOWSQUEUE_HH_
#define __WINDOWSQUEUE_HH_

#include <QtCore>

template <class T>
class WindowsQueue
{
    public:
        WindowsQueue(){};

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
        }

    private:
        QQueue<T> _queue;
        QMutex _queueMutex;

//        long long _pushes;
//        long long _pops;
//        QMutex _pushesMutex;
//        QMutex _popsMutex;
};

#endif
