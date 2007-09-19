#ifndef __STTYCIARUI_COMMON_HH__
#define __STTYCIARUI_COMMON_HH__

#include <QtCore>

#include <boost/shared_ptr.hpp>

using boost::shared_ptr;

class Device;

class SttyciarUI: public QObject
{
    Q_OBJECT
    public:
        static const short EXIT = 0;
        static const short HUB_TYPE = 1;

    public slots:
        virtual void updateStatistics() = 0;
        virtual void receiveDevices(
            const QList<shared_ptr<Device> >& devices ) {};

    protected slots:
        virtual void exit() = 0;

    signals:
        void exitSttyciar();
        void startSttyciar(short deviceType);
        void stopSttyciar();
};

#endif
