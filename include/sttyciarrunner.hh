#ifndef __STTYCIARRUNNER_H__
#define __STTYCIARRUNNER_H__

#include <QtCore>

#include <boost/shared_ptr.hpp>
#include <boost/scoped_ptr.hpp>

#include "abstractionlayer.hh"
#include "alnetworklistener.hh"

#include "sttyciarui_cli.hh"

using boost::shared_ptr;
using boost::scoped_ptr;

//class SttyciarUI;
//class AbstractionLayer;
//class ALNetworkListener;

class SttyciarRunner: public QObject
{
    Q_OBJECT
    public:
        SttyciarRunner();

    private:
        scoped_ptr<SttyciarUI> _ui;
        shared_ptr<AbstractionLayer> _abstractionLayer;
        shared_ptr<ALNetworkListener> _networkLogicLayer;

    private slots:
        void startSttyciar(short deviceType);
        void stopSttyciar();
        void exitSttyciar();
};

#endif
