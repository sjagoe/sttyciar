#ifndef __UILISTENER_HH__
#define __UILISTENER_HH__

#include <QObject>

/*!
The UIListener is a (pure virtual) public interface that is implemented by the
Network Logic Layer so that the User Interface can pass control messages to it.

@author Simon Jagoe
*/
class UIListener: public QObject
{
    Q_OBJECT
    public:
        /*!
        Virtual destructor to allow destructor overriding.
        */
        virtual ~UIListener() {};

};

#endif
