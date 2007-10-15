#ifndef __RENDERABLE_HH__
#define __RENDERABLE_HH__

#include <QPainter>
/*!
Renderable forms the base class for items that will be rendered on the
LoadCanvas.

\author Simon Jagoe
*/
class Renderable
{
    public:
        /*!
        Virtual destructor to ensure that it is called in addition to the
        subclass destructors.
        */
        virtual ~Renderable() {};

        /*!
        Pure virtual method that subclasses override to provide their own
        drawing method.

        \param painter The QPainter used to draw the Renderable onto the
        QWidget canvas.
        */
        virtual void draw( QPainter& painter ) = 0;

        /*!
        Set the position that the Renderable will be drawn at.

        \param position The QPoint location on the canvas to draw the object.
        */
        void setPosition( QPoint& position );

    protected:
        /*!
        Provide read-only access to the position. The position can be changed
        by using the setPosition() method.

        \return A constant reference to the position of the object.
        */
        const QPoint& position();

    private:
        //! The position on the canvas of the object.
        QPoint _position;
};

inline
void Renderable::setPosition( QPoint& position )
{
    this->_position = position;
}

inline
const QPoint& Renderable::position()
{
    return this->_position;
}

#endif
