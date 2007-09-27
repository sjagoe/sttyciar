#ifndef __STATISTICSLAYER_HH__
#define __STATISTICSLAYER_HH__

#include <QtCore>
#include <QMap>
#include <string>
#include <sstream>
#include "alstatisticslistener.hh"

using std::string;
using std::ostringstream;

class StatisticsLayer: public QObject, public ALStatisticsListener
{
    Q_OBJECT
    public:
        StatisticsLayer();
        void updateStatistics(InterfaceRoute& interfaceRoute);
        void initializeTable(QList<shared_ptr<Device> >& devices);
        void clearTable();
        string toString();

    private:
        QMap<shared_ptr<Device>, QMap<shared_ptr<Device>, double> > _traffic;
};

#endif
