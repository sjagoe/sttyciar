#ifndef __STATISTICSLAYER_HH__
#define __STATISTICSLAYER_HH__

#include <QtCore>

#include <QMap>

#include "alstatisticslistener.hh"

class StatisticsLayer: public QObject, public ALStatisticsListener
{
    Q_OBJECT
    public:
        StatisticsLayer();

        void updateStatistics( InterfaceRoute& interfaces );

        void availableInterfaces( QList<shared_ptr<Device> >& devices );

    private:
        QMap<shared_ptr<Device>, QMap<shared_ptr<Device>, long long> > _traffic;
};

#endif
