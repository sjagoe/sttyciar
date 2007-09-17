#ifndef __STTYCIARUI_CLI_MAIN_HH__
#define __STTYCIARUI_CLI_MAIN_HH__

#include <QtCore>

class SttyciarCLIMain: public QObject
{
    Q_OBJECT
    public:
        SttyciarCLIMain();

        void draw();

    signals:
        void redraw();
        void startSttyciar(short deviceType);
        void exit();
};

#endif
