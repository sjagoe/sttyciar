#ifndef __STATISTICS_HH__
#define __STATISTICS_HH__

#include <QtCore>
#include <QMap>

#include <boost/shared_ptr.hpp>

using boost::shared_ptr;

class Device;

/*!
This class contains various statistics about packets being routed through the software.
An object of this type is sent to the GUI from the StatisticsLayer at intervals.

\author Doron Horwitz
*/
class Statistics
{
    public:
        /*!
        Constructor. Takes various information about the packets being passed through the software
        and calculates the required statistics

        \param traffic A matrix of signifying the amount of packets flowing between each of the
        network Devices in a specified time period
        \param totalPackets The total amount of packets routed in the predefined period
        */
        Statistics(shared_ptr<QMap<shared_ptr<Device>,QMap<shared_ptr<Device>,double> > >& traffic,
                   int totalPackets);

        /*!
        Get the percentage of the total traffic that passed between a source and destination Device
        \param source The source Device
        \param destination The destination Device
        \return Not actually a percentage but rather a fraction - easier to work with
        */
        double getTrafficPercentage(shared_ptr<Device> source, shared_ptr<Device> destination);

        /*!
        Get the total amount of packets that were routed in a specified time period
        \return The total amount of packets
        */
        int getTotalPackets() const;

    private:

        shared_ptr<QMap<shared_ptr<Device>,QMap<shared_ptr<Device>,double> > > _percentageTraffic; //!The matrix indicating the percentage of traffic between each network Device
        int _totalPackets; //!The total amount of packets routed in a specific time period

        /*!
        Generate the matrix of traffic percentages
        \param traffic A matrix of signifying the amount of packets flowing between each of the
        network Devices in a specified time period
        \param totalPackets The total amount of packets routed in the predefined period
        */
        void calculateTrafficPercentage(shared_ptr<QMap<shared_ptr<Device>,QMap<shared_ptr<Device>,double> > >& traffic,
                                        int totalPackets);
};

#endif // __STATISTICS_HH__
