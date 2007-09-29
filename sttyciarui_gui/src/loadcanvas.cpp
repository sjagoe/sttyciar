#include <math.h>
#include <algorithm>
#include <iostream>

#include <QPainter>
#include <QStringList>

#include "loadcanvas.hh"
#include "loadlabel.hh"

#include "device.hh"

const int LoadCanvas::MINIMUM_SIZE_HINT;
const int LoadCanvas::SIZE_HINT;

const int LoadCanvas::MAX_PEN_WIDTH;

const double LoadCanvas::PI;

LoadCanvas::LoadCanvas(QWidget* parent)
    : QWidget(parent)
{
    //this->_statistics.reset( new Statistics );
    // get the width and height of the canvas
    this->_width = width();
    this->_height = height();

    // determine the centre
    this->_centre.setX( this->_width/2 );
    this->_centre.setY( this->_height/2 );

    // subtract 1 to be certain that it is within the bounds of the area
    // (as we are always using integer division).
    this->_radius = (std::min( this->_width, this->_height )/2) - 1;

    //this->_pen.setWidth(2);

    this->setBackgroundRole( QPalette::Base );
    this->setAutoFillBackground(true);

    this->setMinimumSize( this->minimumSizeHint() );

//    shared_ptr<Device> d( new Device );
//    QStringList l;
//    l << QString("0.0.0.0") << QString("192.168.80.1") << QString("0.0.45.0");
//
//    QMap<shared_ptr<Device>, QStringList> m;
//    m.insert( d, l );
//
//    l.clear();
//    d.reset( new Device );
//    l << QString("0.0.0.0") << QString("146.141.117.1") << QString("0.0.46.0");
//    m.insert (d, l);
//
//    l.clear();
//    d.reset( new Device );
//    l << QString("0.0.0.0") << QString("10.0.0.1") << QString("0.1.45.0");
//    m.insert (d, l);
//
//    l.clear();
//    d.reset( new Device );
//    l << QString("0.0.0.0") << QString("128.86.55.3") << QString("0.0.45.4");
//    m.insert (d, l);
//
//    this->setLabels( m );
}

QSize LoadCanvas::minimumSizeHint() const
{
    return QSize(MINIMUM_SIZE_HINT, MINIMUM_SIZE_HINT);
}

QSize LoadCanvas::sizeHint() const
{
    return QSize(SIZE_HINT, SIZE_HINT);
}

void LoadCanvas::setLabels( const QList<shared_ptr<Device> >& devices )
{
    // get the number of labels so that they can be spaced correctly
    int size = devices.size();
    double angleIncrement = 2*PI/size;
    double angle = 0;

    // QFontMetrics to get the text dimensions
    QFontMetrics fm = this->fontMetrics();
    int baseHeight = fm.lineSpacing();

    // iterate through devices
    foreach ( shared_ptr<Device> device, devices )
    {
        // a stringlist to contain ip addresses as labels
        QStringList labels;

        // iterate through device IP addresses
        QList<DeviceAddress> addrList = device->getAddresses();
        foreach ( DeviceAddress address, addrList )
        {
            // Add the IP to the string list
            labels << QString(address.getAddress().toIPString().data());
        }

        // create a QPair to put into the LoadLabel map
        QPair<double, shared_ptr<LoadLabel> > value;

        // set the angle that the label will be at on the circle.
        value.first = angle;
        // create a LoadLabel object and initialise it with the label string
        QString separator( "\n" );
        QString oneLineLabel = labels.join(separator);
        value.second.reset(new LoadLabel(oneLineLabel));

        // set the width of the label
        int w = 0;
        foreach (QString labelPart, labels)
        {
            w = max(w, fm.width(labelPart));
        }
        value.second->setWidth(w);

        // set the height of the label
        int h = baseHeight * labels.size();
        value.second->setHeight(h);

        this->_labels.insert( device, value );

        angle += angleIncrement;
    }
}

void LoadCanvas::updateStatistics( shared_ptr<Statistics> stats )
{
    if (this->_statistics.get() != stats.get())
        this->_statistics = stats;
}

void LoadCanvas::paintEvent( QPaintEvent* /* event */ )
{
    // calculate the positions for the labels and the radius.
    if (this->checkResized())
    {
        this->recalculateCanvasSize();
    }

    QPainter painter(this);
    painter.setPen(this->_pen);
    painter.drawEllipse( (this->_centre.x() - this->_radius),
                         (this->_centre.y() - this->_radius),
                          this->_radius*2, this->_radius*2 );

    QPair<double, shared_ptr<LoadLabel> > label;
    foreach (label, _labels)
    {
        label.second->draw(painter);
    }

    // draw the lines
    if (this->_statistics.get() != 0)
    {
        QMap<shared_ptr<Device>, QPair<double, shared_ptr<LoadLabel> > >::const_iterator row = this->_labels.begin();

        for (; row != this->_labels.end(); row++)
        {
            std::cout << "1" << std::endl;
            QMap<shared_ptr<Device>, QPair<double, shared_ptr<LoadLabel> > >::const_iterator column = this->_labels.begin();

            for (; column != this->_labels.end(); column++)
            {
                std::cout << "2" << std::endl;
                if (row.key().get() != column.key().get())
                {
                    std::cout << "3" << std::endl;
                    double total = this->_statistics->getTrafficPercentage( row.key(), column.key() );
                    total += this->_statistics->getTrafficPercentage( column.key(), row.key() );

                    double startAngle = this->_labels.value( row.key() ).first;
                    double endAngle = this->_labels.value( column.key() ).first;

                    QPoint start;
                    start.setX( (int)((double)this->_radius * cos(startAngle)) );
                    start.setY( -1*(int)((double)this->_radius * sin(startAngle)) );
                    QPoint end;
                    end.setX( (int)((double)this->_radius * cos(endAngle)) );
                    end.setY( -1*(int)((double)this->_radius * cos(endAngle)) );
                }
            }
        }
    }
}

bool LoadCanvas::checkResized()
{
    int width = this->width();
    int height = this->height();

    bool changed = false;

    if (width != this->_width)
    {
        // store the width
        this->_width = width;
        // determine the centre
        this->_centre.setX( this->_width/2 );
        // set a flag to calculate the radius
        changed = true;
    }
    if (height != this->_height)
    {
        // store the height
        this->_height = height;
        // determine the centre
        this->_centre.setY( this->_height/2 );
        // set a flag to calculate the radius
        changed = true;
    }
    return changed;
}

void LoadCanvas::recalculateCanvasSize()
{
    QFontMetrics fm = this->fontMetrics();
    //int fontHeight = fm.lineSpacing() * 2;
    int fontHeight = 0;

    int fontWidth = 0;
    QPair<double, shared_ptr<LoadLabel> > item;
    foreach ( item, _labels )
    {
        //fontWidth = std::max( fontWidth, fm.width( item.second->getLabel() ) );
        fontWidth = std::max( fontWidth, item.second->getWidth() );
        fontHeight = std::max( fontHeight, item.second->getHeight() );
        if ( item.first < 0 )
        {
            item.first += ( 2 * PI );
        }
    }
    fontWidth += fm.maxWidth();
    fontHeight += fm.lineSpacing();

    int radiusHeight = (int)floor( this->_height/2 ) - fontHeight;
    int radiusWidth = (int)floor( this->_width/2 ) - fontWidth;

    this->_radius = std::min( radiusWidth, radiusHeight );

    int tempRadius = this->_radius + (fm.lineSpacing()/2);

    foreach( item, _labels )
    {
        // get the angle
        double angle = item.first;
        // get the LoadLabel
        shared_ptr<LoadLabel> label = item.second;
        // determine the X value of the position
        int x = (int)( (double)tempRadius * cos( angle ) );
        // correct for the width of the text
        int halfWidth = label->getWidth()/2;
        x -= halfWidth;
        // place outside of the circle based on angle
        x += (int)( (double)halfWidth * cos( angle ) );

        // determine the Y value of the position
        int y = -1*(int)( (double)tempRadius * sin( angle ) );
        // correct for the height of the text
        int halfHeight = label->getHeight()/2;
        y -= halfHeight;
        // place outside of the circle based on angle
        y += -1*(int)( (double)halfHeight * sin( angle ) );

        // create the position QPoint and translate it relative to the centre of the canvas
        QPoint position( x, y );
        position += _centre;
        // set the LoadLabel object's position
        label->setPosition( position );

    }
}
