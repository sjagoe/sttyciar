#ifndef __STATISTICS_HH__
#define __STATISTICS_HH__

#include <QtCore>
#include <QMap>

class Statistics
{
    Q_OBJECT
    public:
        Statistics();
        double calculateTrafficPercentage(QMap<shared_ptr
        double getTrafficPercentage(shared_ptr<Device> source, shared_ptr<Device> destination);

    private:
        QMap<shared_ptr<Device>,QMap<shared_ptr<Device>,double> > _percentageTraffic;
};

#endif // __STATISTICS_HH__
