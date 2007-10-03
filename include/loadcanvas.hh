#ifndef __LOADCANVAS_HH__
#define __LOADCANVAS_HH__

// Qt
#include <QWidget>
#include <QPen>
//#include <QMap>
#include <QList>
#include <QPair>
#include <QString>

// Boost
#include <boost/shared_ptr.hpp>

// Local
#include "loadlabel.hh"
#include "device.hh"
#include "statistics.hh"

using boost::shared_ptr;

//class LoadLabel;
//class Device;

/*!
The canvas (custom drawn) Qt Widget that will render the Load Visualisation.

\author Simon Jagoe
*/
class LoadCanvas: public QWidget
{
    Q_OBJECT
    public:
        /*!
        Construct the widget with no labels, but calculate the sizes and other
        paramaters.

        \param parent The parent widget, passed to the QWidget constructor.
        */
        LoadCanvas(QWidget* parent = 0);

        /*!
        Return the preferred minimum size of the widget.
        */
        QSize minimumSizeHint() const;

        /*!
        Return the preferred size of the widget.
        */
        QSize sizeHint() const;

    public slots:
        /* !
        Set the device labels that will be displayed around the circle.

        \param labels A QMap relating a Device pointer to a QString label.
        */
        //void setLabels( const QMap<shared_ptr<Device>, QStringList>& labels );

        /*!
        Set the device labels that will be displayed around the circle.

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

    protected:
        /*!
        Over-ridden Qt method that is called when the main event loop needs to
        redraw the widget.
        */
        void paintEvent( QPaintEvent* event );

    private:
        QPoint _centre; //! The centre of the canvas
        int _width; //! The width of the widget
        int _height; //! The height of the widget

        int _radius; //! The radius of the circle in which the statistics are displayed

        QPen _pen; //! The QPen that will be used to render the view
        QMap<shared_ptr<Device>, QPair<double, shared_ptr<LoadLabel> > > _labels; //! Labels placed on the visualisation for each of the interfaces bound to the device. Key == Device, Value.first == angle, Value.second == LoadLabel.

        static const int MINIMUM_SIZE_HINT = 400; //! Minimum size hint of the widget
        static const int SIZE_HINT = 500; //! Size hint of the widget
        static const double PI = 3.141593; //! constant pi, used in polar coordinate conversions

        static const int MAX_PEN_WIDTH = 35; //! The pen width depicting maximum/all traffic

        shared_ptr<Statistics> _statistics;

        /*!
        Check if the widget has been resized, and store the new size in class variables.

        \return true if the widget has been resized, false otherwise.
        */
        bool checkResized();

        /*!
        Recalculate the positions od size of objects on the canvas when the
        canvas has been resized.
        */
        void recalculateCanvasSize();
};

#endif
