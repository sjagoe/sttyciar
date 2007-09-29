#ifndef __STATISTICSLAYER_HH__
#define __STATISTICSLAYER_HH__

#include <QtCore>
#include <QMap>
#include <string>
#include <sstream>
#include "alstatisticslistener.hh"

using std::string;
using std::ostringstream;

class Statistics;

class StatisticsLayer: public QObject, public ALStatisticsListener
{
    Q_OBJECT
    public:
        StatisticsLayer();
        void updateStatistics(shared_ptr<InterfaceRoute>& interfaceRoute);
        void initializeTable(QList<shared_ptr<Device> >& devices);
        void clearTable();
        shared_ptr<Statistics> getStatistics();
        string toString();

    private:
        shared_ptr<QMap<shared_ptr<Device>, QMap<shared_ptr<Device>, double> > > _traffic;
        int _totalPackets;

    public slots:
        void calculate();

    signals:
        void sendStats(shared_ptr<Statistics>& slots);

};

#endif
