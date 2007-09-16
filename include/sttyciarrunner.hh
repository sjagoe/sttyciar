#ifndef __STTYCIARRUNNER_H__
#define __STTYCIARRUNNER_H__

#include <QtCore>

#include <boost/shared_ptr.hpp>

#include "uilistener.hh"

using boost::shared_ptr;

class AbstractionLayer;
class ALNetworkListener;

class SttyciarRunner : public UIListener
{
    Q_OBJECT
    public:
        SttyciarRunner();
};

#endif
