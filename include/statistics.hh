#ifndef __STATISTICS_HH__
#define __STATISTICS_HH__

#include <QtCore>
#include <QMap>

#include <boost/shared_ptr.hpp>

using boost::shared_ptr;

class Device;

class Statistics
{
    public:
        Statistics();
        //double calculateTrafficPercentage(QMap<shared_ptr
        double getTrafficPercentage(shared_ptr<Device> source, shared_ptr<Device> destination);

    private:
        QMap<shared_ptr<Device>,QMap<shared_ptr<Device>,double> > _percentageTraffic;
};

#endif // __STATISTICS_HH__
