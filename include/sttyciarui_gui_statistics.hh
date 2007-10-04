#ifndef __STTYCIARUI_GUI_STATISTICS_HH__
#define __STTYCIARUI_GUI_STATISTICS_HH__

//#include <iostream>

#include <QMainWindow>

#include <boost/shared_ptr.hpp>

using boost::shared_ptr;

// Qt Forward Declerations
class QHBoxLayout;
class QPushButton;
class QWidget;
class QTabWidget;
class QGroupBox;
class QTableWidget;
class QLabel;
class QLineEdit;
class QComboBox;
class QStringList;

// Local Forward Declerations
class LoadCanvas;
class LoadTable;
class Device;
class Statistics;

/*!
A Qt QMainWindow subclass that provides the statistics view form.

\author Simon Jagoe
*/
class SttyciarGUIStatistics: public QMainWindow
{
    Q_OBJECT
    public:
        /*!
        Default constructor to set up the UI layout and connect the signals and
        slots. The \a parent parameter is passed to the \c QMainWindow
        constructor.

        \param parent QWidget parent of the object, passed to the \c QMainWindow
        constructor.
        */
        SttyciarGUIStatistics(QMap<int, QString> networkDevices, QWidget* parent = 0);

    public slots:
        /*!
        Pass the activated Devices to the UI to extract lavels for the
        visualisation.

        \param devices a \c QList of \c Device \c shared_ptrs that have been
        activated in the AbstractionLayer (and obtained using
        AbstractionLayer::getActivatedDevices()).
        */
        void receiveActivatedDevices(
            const QList<shared_ptr<Device> >& devices,
            const QString& deviceType,
            const shared_ptr<QStringList>& deviceList,
            const QString& dumpFile );

        /*!
        Slot called by the statistics layer when updated statistics are
        available. This slot updates all of the views on the form.

        \param stats The \a Statistics object that contains the information to
        be displayed.
        */
        void updateStatistics( shared_ptr<Statistics> stats );

    private:
        //! lay out the device-switching section
        void setupDeviceSelection(QMap<int, QString> networkDevices);
        //! Lay out the TabWidget
        void setupTabWidget();
        //! Lay out the Rates group box
        void setupRates();
        //! Lay out the buttons
        QHBoxLayout* setupButtons();

        QGroupBox* _grpChangeDevice; //! Group box to contain the widgets that change the device type
        QLabel* _lblChangeDevice; //! label displaying the function of the combo box
        QComboBox* _comboChangeDevice; //! combo box to select the new device type

        QTabWidget* _tabs; //! A QTabWidget providing a tabbed pane to select a statistics view/set.

        LoadCanvas* _graphLoad; //! A LoadCanvas object to draw a graphical visualisation of the traffic load in the device.
        //QTableWidget* _tblTextualLoad; //! A QTableWidget to provide the load information in tabular form.
        LoadTable* _tblLoad; //! A widget containing a table to display percentage load stats
        LoadTable* _tblPackets; //! A widget containing a table to display actual load (in number of packets) stats

        QGroupBox* _grpRates; //! A QGroupBox to lay out the rates section (packets per second and bytes per second)
        QLabel* _lblPacketsPerSecond; //! A QLabel to label the packets per second field
        QLineEdit* _edtPacketsPerSecond; //! A QLineEdit to display the Packets per Second value
        QLabel* _lblBytesPerSecond; //! A QLabel to label the bytes per second field
        QLineEdit* _edtBytesPerSecond; //! A QLineEdit to display the Bytes per Second value
        QLabel* _lblKBytesPerSecond; //! QLabel to label the kilobytes per second field
        QLineEdit* _edtKBytesPerSecond; //! QLineEdit to display the kilobytes per second field

        QLabel* _lblDumpBuffer; //! label the Dump Buffer Contents field
        QLineEdit* _edtDumpBuffer; //! QLineEdit to display the size of the packet dump buffer

        QPushButton* _exitButton; //! QPushButton to exit the application
        QPushButton* _stopButton; //! QPushButton to stop the application

        QWidget* _centralWidget; //! A dummy widget used to layout the form correctly.

        shared_ptr<Statistics> _statistics; //! Store a statistics object with the data to display

        QString _dumpFile; //! File used to dump packets. Needed if the device is restarted
        shared_ptr<QStringList> _devices; //! List to store the activated devices. Needed if the device is restarted

    private slots:
        /*!
        catch combo-box changed events to emit a restart sttyciar signal.
        */
        void deviceChanged(const QString& text);

    signals:
        //! Signal emitted when the Exit button is clicked
        void exit();
        //! Signal emitted when the Stop button is clicked
        void stopSttyciar();
        //! signal to restart the device as something else
        void restartSttyciar( const QString& deviceType,
            const shared_ptr<QStringList>& devices,
            const QString& dumpFile );
};

#endif
