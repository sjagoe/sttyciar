#ifndef __LOADTABLE_HH_
#define __LOADTABLE_HH_

#include <QWidget>
#include <QList>

#include <boost/shared_ptr.hpp>

#include "device.hh"

using boost::shared_ptr;

class QTableWidget;

class Statistics;

/*!
A Table widget to display statistics from the network device.

\author Simon Jagoe
*/
class LoadTable: public QWidget
{
    Q_OBJECT
    public:
        /*!
        Construct the widget with no labels or columns

        \param parent The parent widget, passed to the QWidget constructor.
        */
        LoadTable(bool percentage = false, int threshold = -1, QWidget* parent = 0);

        /*!
        Return the preferred minimum size of the table.
        */
        QSize minimumSizeHint() const;

        /*!
        Return the preferred size of the table.
        */
        QSize sizeHint() const;

    public slots:
        /*!
        Set the device labels that will be displayed in the row and column
        headers.

        \param devices A QList containing all of the devices used in the system,
        from which the labels will be extracted.
        */
        void setLabels( const QList<shared_ptr<Device> >& devices );

        /*!
        Update the statistics display with the values contained in the
        Statistics object passed.

        \param table The QMap<QMap> table containing the statistics
        */
        void updateStatistics( shared_ptr<QMap<shared_ptr<Device>,QMap<shared_ptr<Device>,double> > > table );

    private:
        QTableWidget* _tblLoad; //! The table used to display the information

        QMap<shared_ptr<Device>, int> _devices; //! Devices and corresponding row/column

        shared_ptr<QMap<shared_ptr<Device>,QMap<shared_ptr<Device>,double> > > _table; //! The table of data to display

        bool _percentage; //! store whether or not to display as a percentage value

        int _threshold; //! Threshold for when the display changes to xxxk, or xxxM etc.
};

#endif
