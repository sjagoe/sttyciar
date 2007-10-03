#ifndef __LOADTABLE_HH_
#define __LOADTABLE_HH_

#include <QWidget>
#include <QList>

#include <boost/shared_ptr.hpp>

#include "device.hh"

using boost::shared_ptr;

class QTableWidget;

class Statistics;

class LoadTable: public QWidget
{
    Q_OBJECT
    public:
        /*!
        Construct the widget with no labels or columns

        \param parent The parent widget, passed to the QWidget constructor.
        */
        LoadTable(QWidget* parent = 0);

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

        \param stats Statistics object containing the information to display.
        */
        void updateStatistics( shared_ptr<Statistics>& stats );

    private:
        QTableWidget* _tblLoad;

        QMap<shared_ptr<Device>, int> _devices;
};

#endif
