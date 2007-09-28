#ifndef __STTYCIARUI_COMMON_HH__
#define __STTYCIARUI_COMMON_HH__

#include <QtCore>

#include <boost/shared_ptr.hpp>

using boost::shared_ptr;

class Device;
class Statistics;

/*!
Abstract base class for all Qt User Interfaces, which defined the public
programming interface.

\author Simon Jagoe
*/
class SttyciarUI: public QObject
{
    Q_OBJECT
    //public:
        //static const short EXIT = 0; // ! Constant defining the exit signal
        //static const short HUB_TYPE = 1;

    public slots:
        /*!
        Slot enabling the user interface to be informed that Sttyciar is now running.
        This should display the Statistics form of the UI.
        */
        virtual void sttyciarRunning() = 0;

        /*!
        Slot enabling the user interface to be informed that Sttyciar is no longer running.
        This should return the display to the main setup form.
        */
        virtual void sttyciarStopped() = 0;

        /*!
        Provides the UI with updated traffic statistics for displaying.

        \param stats A pointer to the Statistics object constructed by the StatisticsLayer.
        */
        virtual void updateStatistics( shared_ptr<Statistics> stats ) = 0;

        /*!
        Send a complete list of devices for display on the main UI, allowing
        the user to select devices to use.

        \param devices A QList of Device shared pointers
        */
        virtual void receiveDevices(
            const QList<shared_ptr<Device> >& devices ) = 0;
        virtual void receiveActivatedDevices(
            const QList<shared_ptr<Device> >& devices ) = 0;

    protected slots:
        virtual void exit() = 0;

    signals:
        void exitSttyciar();
        void startSttyciar(QString deviceType, shared_ptr<QStringList> devices);
        void stopSttyciar();
};

#endif
