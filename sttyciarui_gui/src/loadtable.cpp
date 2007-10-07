//#include <iostream>

#include <Qt>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHBoxLayout>
#include <QStringList>
#include <QString>
#include <QHeaderView>

#include "loadtable.hh"
//#include "device.hh"
#include "statistics.hh"

LoadTable::LoadTable(bool percentage, int threshold, QWidget* parent)
    : QWidget(parent)
{
    this->_percentage = percentage;
    this->_threshold = threshold;
    this->_tblLoad = new QTableWidget;
    this->_tblLoad->verticalHeader()->setDefaultAlignment( Qt::AlignCenter );
    this->_tblLoad->setSelectionMode( QAbstractItemView::NoSelection );
    this->_tblLoad->setEditTriggers( QAbstractItemView::NoEditTriggers );

    QHBoxLayout* l = new QHBoxLayout;
    l->addWidget( this->_tblLoad );
    this->setLayout(l);
}

QSize LoadTable::minimumSizeHint() const
{
    if (this->_tblLoad)
    {
        return this->_tblLoad->minimumSizeHint();
    }
    else
    {
        return QSize(0,0);
    }
}

QSize LoadTable::sizeHint() const
{
    if (this->_tblLoad)
    {
        return this->_tblLoad->sizeHint();
    }
    else
    {
        return QSize(0,0);
    }
}

void LoadTable::setLabels( const QList<shared_ptr<Device> >& devices )
{
    int numDevices = devices.size();
    this->_tblLoad->clear();
    this->_tblLoad->setRowCount(numDevices);
    this->_tblLoad->setColumnCount(numDevices);
    // QFontMetrics to get the text dimensions
    QFontMetrics fm = this->fontMetrics();
    int baseHeight = fm.lineSpacing();

    QStringList tableLabels;

    // iterate through devices
    int currentRow = 0;
    foreach ( shared_ptr<Device> device, devices )
    {
        // a stringlist to contain ip addresses as labels
        this->_devices.insert( device, currentRow );
        QStringList labels;

        // iterate through device IP addresses
        QList<DeviceAddress> addrList = device->getAddresses();
        foreach ( DeviceAddress address, addrList )
        {
            // Add the IP to the string list
            labels << QString(address.getAddress().toIPString().data());
        }

        // create a single string with the multi-line label
        QString separator( "\n" );
        QString oneLineLabel = labels.join(separator);

        // get the width of the label
        //int w = 0;
        //foreach (QString labelPart, labels)
        //{
        //    w = max(w, fm.width(labelPart));
        //}

        // get the height of the label
        int h = baseHeight * (labels.size() + 1);

        // put each single QString label into the string list of Header Labels
        tableLabels << oneLineLabel;
        this->_tblLoad->setRowHeight( currentRow, h );

        // increment the current row reference
        currentRow++;
    }
    this->_tblLoad->setHorizontalHeaderLabels( tableLabels );
    this->_tblLoad->setVerticalHeaderLabels( tableLabels );
}

void LoadTable::updateStatistics( shared_ptr<QMap<shared_ptr<Device>,QMap<shared_ptr<Device>,double> > > table )
{
    this->_table = table;
    if (this->_table.get() != 0)
    {
        QMap<shared_ptr<Device>, int>::const_iterator row = this->_devices.begin();
        for (; row != this->_devices.end(); row++)
        {
            QMap<shared_ptr<Device>, int>::const_iterator column = this->_devices.begin();
            for (; column != this->_devices.end(); column++)
            {
                // get the amount of traffic between two interfaces
                //double traffic = stats->getTrafficPercentage( row.key(), column.key() );
                double traffic = this->_table->value( row.key() ).value( column.key() );
                QString item;
//                std::cout << traffic << " ";
                if (this->_percentage)
                {
                    traffic *= 100;
                    item = QString("%1%").arg(traffic, 0, 'f', 2);
                }
                else if (this->_threshold == -1)
                {
                    item = QString("%1").arg(traffic);//, 0, 'f', 2);
                }
                else
                {
                    QString mult = "";
                    if (traffic >= this->_threshold)
                    {
                        traffic /= this->_threshold;
                        mult = "k";
                        if (traffic >= this->_threshold)
                        {
                            traffic /= this->_threshold;
                            mult = "M";
                        }
                    }
                    item = QString("%1").arg(traffic, 0, 'f', 2);
                    item.append( mult );
                }

                QTableWidgetItem* tableItem = this->_tblLoad->item( row.value(), column.value() );
                if (tableItem == 0)
                    tableItem = new QTableWidgetItem;
                tableItem->setText(item);

                this->_tblLoad->setItem( row.value(), column.value(), tableItem);
            }
        }
//        std::cout << std::endl << std::endl;
    }
}
//{
//    if (stats.get() != 0)
//    {
//        //QMap<shared_ptr<Device>, QPair<double, shared_ptr<LoadLabel> > >::const_iterator row = this->_labels.begin();
//        QMap<shared_ptr<Device>, int>::const_iterator row = this->_devices.begin();
//
//        //for (; row != this->_labels.end(); row++)
//        for (; row != this->_devices.end(); row++)
//        {
//            //QMap<shared_ptr<Device>, QPair<double, shared_ptr<LoadLabel> > >::const_iterator column = this->_labels.begin();
//            QMap<shared_ptr<Device>, int>::const_iterator column = this->_devices.begin();
//
//            //for (; column != this->_labels.end(); column++)
//            for (; column != this->_devices.end(); column++)
//            {
//                //if (row.key().get() != column.key().get())
//                {
//                    // get the amount of traffic between two interfaces
//                    double traffic = stats->getTrafficPercentage( row.key(), column.key() );
//                    traffic *= 100;
//                    QString item = QString("%1%").arg(traffic, 0, 'f', 2);
//
//                    QTableWidgetItem* tableItem = this->_tblLoad->item( row.value(), column.value() );
//                    if (tableItem == 0)
//                        tableItem = new QTableWidgetItem;
//                    tableItem->setText(item);
//
//                    this->_tblLoad->setItem( row.value(), column.value(), tableItem);
//                }
//            }
//        }
//    }
//}
