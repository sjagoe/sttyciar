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
        Statistics(shared_ptr<QMap<shared_ptr<Device>,QMap<shared_ptr<Device>,double> > >& traffic,
                   int totalPackets);
        double getTrafficPercentage(shared_ptr<Device> source, shared_ptr<Device> destination);
        int getTotalPackets() const;

    private:
        shared_ptr<QMap<shared_ptr<Device>,QMap<shared_ptr<Device>,double> > > _percentageTraffic;
        int _totalPackets;
        void calculateTrafficPercentage(shared_ptr<QMap<shared_ptr<Device>,QMap<shared_ptr<Device>,double> > >& traffic,
                                        int totalPackets);
};

#endif // __STATISTICS_HH__
