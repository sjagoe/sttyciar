#ifndef __LOADLABEL_HH__
#define __LOADLABEL_HH__

#include <QString>
#include <QPoint>

#include "renderable.hh"

/*!
The LoadLabel class provides a renderable label for devices around the perimiter
of the traffic load visualisation.

\author Simon Jagoe
*/
class LoadLabel: public Renderable
{
    public:
        /*!
        Construct a LoadLabel with a default generic label, and at position 0,0.
        */
        LoadLabel();

        /*!
        Construct a LoadLabel with the provided label and postition
        (default 0,0).

        \param label The text label displayed by the LoadLabel.
        \param position The position on the canvas to render the label.
        */
        LoadLabel( QString label, QPoint position = QPoint() );

        /*!
        Virtual destructor because the class has virtual functions (inherited).
        */
        virtual ~LoadLabel() {};

        /*!
        Overridden Renderable::draw() method, providing the LoadLabel specific
        drawing method.

        \param position The QPoint location on the canvas to draw the object.
        */
        void draw( QPainter& painter );

        /*!
        Return the QString label of the LoadLabel.

        \return Label that is displayed on the canvas.
        */
        QString& getLabel();

        /*!
        Set the label that will be displayed on the canvas.

        \param label Set the label displayed on the canvas.
        */
        void setLabel( QString& label );

        /*!
        Set the height of the label. This is used to determine the size of the
        bounding box. And incorrect size may clip the text, or place it badly
        on the canvas.

        \param height The height calculated using a QFontMetrics object
        */
        void setHeight( int& height );

        /*!
        Set the width of the label. This is used to determine the size of the
        bounding box. And incorrect size may clip the text, or place it badly
        on the canvas.

        \param width The width calculated using a QFontMetrics object
        */
        void setWidth( int& width );

        /*!
        Return the width previously set with setWidth().

        \return The width of the label.
        */
        const int& getWidth();

        /*!
        Return the height previously set with setWidth().

        \return The height of the label.
        */
        const int& getHeight();

    private:
        //! The label displayed on the canvas.
        QString _label;

        //! The total height of the label
        int _height;

        //! The total width of the label
        int _width;
};

#endif
