#ifndef __STTYCIARUI_COMMON_HH__
#define __STTYCIARUI_COMMON_HH__

#include <QtCore>

#include <boost/shared_ptr.hpp>

using boost::shared_ptr;

class SttyciarUIMain;
class SttyciarUIStatistics;

//class SttyciarUIBase;

class SttyciarUI: public QObject
{
    Q_OBJECT
    protected:
        shared_ptr<SttyciarUIMain> _mainUI;
        shared_ptr<SttyciarUIStatistics> _statisticsUI;
//
//        shared_ptr<SttyciarUIBase> _currentUI;

    public slots:
        virtual void updateStatistics() = 0;

    protected slots:
        virtual void showMain() = 0;
        virtual void showStatistics() = 0;

    signals:
        void startSttyciar(QString deviceType);
        void stopSttyciar();
};

#endif
