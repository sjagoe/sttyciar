#ifndef __STTYCIARUI_GUI_HH__
#define __STTYCIARUI_GUI_HH__

#include <iostream>

#include <boost/scoped_ptr.hpp>

#include "sttyciarui_common.hh"
#include "sttyciarui_gui_main.hh"
#include "sttyciarui_gui_statistics.hh"

#include "device.hh"

using boost::scoped_ptr;

class SttyciarGUI: public SttyciarUI
{
    Q_OBJECT
    public:
        SttyciarGUI();

    public slots:
        void sttyciarRunning();

        void updateStatistics();

        void receiveDevices( const QList<shared_ptr<Device> >& devices );

    protected slots:
        void exit();

        void startSttyciar(short deviceType);

    private:
        scoped_ptr<SttyciarGUIMain> _mainUI;
        scoped_ptr<SttyciarGUIStatistics> _statisticsUI;
};

#endif
