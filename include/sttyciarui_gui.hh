#ifndef __STTYCIARUI_GUI_HH__
#define __STTYCIARUI_GUI_HH__

#include <iostream>

#include <boost/scoped_ptr.hpp>

#include "sttyciarui_common.hh"
#include "sttyciarui_gui_main.hh"

using boost::scoped_ptr;

class SttyciarGUI: public SttyciarUI
{
    Q_OBJECT
    public:
        SttyciarGUI();

    public slots:
        void updateStatistics() {};


    protected slots:
        void exit() {};

        void startSttyciar(short deviceType)
        {
            //std::cout << deviceType << std::endl;
        };

    private:
        scoped_ptr<SttyciarGUIMain> _mainUI;
};

#endif
