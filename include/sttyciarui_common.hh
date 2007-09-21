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
        virtual void sttyciarRunning() = 0;
        virtual void sttyciarStopped() = 0;
        virtual void updateStatistics() = 0;
        virtual void receiveDevices(
            const QList<shared_ptr<Device> >& devices ) = 0;

    protected slots:
        virtual void exit() = 0;

    signals:
        void exitSttyciar();
        void startSttyciar(QString deviceType, shared_ptr<QStringList> devices);
        void stopSttyciar();
};

#endif
