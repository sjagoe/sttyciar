#ifndef __STTYCIARUI_GUI_HH__
#define __STTYCIARUI_GUI_HH__

//#include <iostream>

#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>

#include "sttyciarui_common.hh"
#include "sttyciarui_gui_main.hh"
#include "sttyciarui_gui_statistics.hh"

#include "device.hh"

using boost::scoped_ptr;
using boost::shared_ptr;

class SttyciarGUI: public SttyciarUI
{
    Q_OBJECT
    public:
        SttyciarGUI(QMap<int, QString>& networkDevices);

    public slots:
        void sttyciarRunning();

        void sttyciarStopped();

        void updateStatistics();

        void receiveDevices( const QList<shared_ptr<Device> >& devices );

    protected slots:
        void exit();

        void startSttyciarSlot(QString deviceType, shared_ptr<QStringList> devices);

        void stopSttyciarSlot();

    private:
        scoped_ptr<SttyciarGUIMain> _mainUI;
        scoped_ptr<SttyciarGUIStatistics> _statisticsUI;
        QMap<int, QString> _availableNetworkDevices;
};

#endif
