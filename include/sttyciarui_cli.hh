#ifndef __STTYCIARUI_CLI_HH__
#define __STTYCIARUI_CLI_HH__

#include "sttyciarui_common.hh"

class SttyciarCLIMain;
class SttyciarCLIStatistics;

class SttyciarCLI: public SttyciarUI
{
    Q_OBJECT
    private:
        bool _statisticsVisible;
        shared_ptr<SttyciarCLIMain> _mainUI;
        shared_ptr<SttyciarCLIStatistics> _statisticsUI;

    public:
        SttyciarCLI();

    public slots:
        void updateStatistics();

    protected slots:
        void exit();

    private slots:
        void showMain();
        void showStatistics();
};

#endif
