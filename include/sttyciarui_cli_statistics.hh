#ifndef __STTYCIARUI_CLI_STATISTICS_HH__
#define __STTYCIARUI_CLI_STATISTICS_HH__

#include <QtCore>

class SttyciarCLIStatistics: public QObject
{
    Q_OBJECT
    public:
        SttyciarCLIStatistics();

    public slots:
        void draw();

    signals:
        void exit();
        void stopSttyciar();
        void redraw();
};

#endif
