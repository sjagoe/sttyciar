//#include <Qt>
#include <QRect>
//#include <iostream>

#include "loadlabel.hh"

LoadLabel::LoadLabel()
{
    QString label( "No Label" );
    setLabel(label);
    QPoint position( 0, 0 );
    this->_height = 0;
    this->_width = 0;
    setPosition(position);
}

LoadLabel::LoadLabel( QString label, QPoint position )
{
    setLabel(label);
    setPosition(position);
}

void LoadLabel::draw( QPainter& painter )
{
    QPoint topLeft = this->position();


    //topLeft -= QPoint( 50,50 );
    //std::cout << topLeft.x() << "  " << topLeft.y() << std::endl;

    //topLeft -= (size);

    QPoint bottomRight = topLeft;//this->position();
    bottomRight += QPoint( this->_width, this->_height );
    //bottomRight += size;

    QRect r(this->position(), bottomRight);

    //painter.drawText(this->position(), this->_label);
    painter.drawText( r, Qt::AlignCenter, this->_label );
}

QString& LoadLabel::getLabel()
{
    return this->_label;
}

void LoadLabel::setLabel( QString& label )
{
    this->_label = label;
}

void LoadLabel::setHeight( int& height )
{
    this->_height = height;
}

void LoadLabel::setWidth( int& width )
{
    this->_width = width;
}

const int& LoadLabel::getWidth()
{
    return this->_width;
}

const int& LoadLabel::getHeight()
{
    return this->_height;
}
