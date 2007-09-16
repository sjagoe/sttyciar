#ifndef __STTYCIARUI_COMMON_HH__
#define __STTYCIARUI_COMMON_HH__

#include <QtCore>

#include <boost/shared_ptr.hpp>

using boost::shared_ptr;

//class SttyciarUIBase;

class SttyciarUI: public QObject
{
    Q_OBJECT
    public slots:
        virtual void updateStatistics() = 0;

    protected slots:
        virtual void exit() = 0;

    signals:
        void stopSignal();
        void exitSignal();
        void startSttyciar(QString deviceType);
        void stopSttyciar();
};

#endif
