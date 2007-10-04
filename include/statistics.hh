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
        \param totalBytes The total amount of bytes routed in the predefined period
        \param timePeriodMillis The time period over which the statistics are to be calculated
        \param awaitingDumpedPackets The amount of packets waiting to be written to file the PacketDumper
        */
        Statistics(shared_ptr<QMap<shared_ptr<Device>,QMap<shared_ptr<Device>,double> > >& traffic,
                   unsigned int totalPackets,unsigned int totalBytes,unsigned int timePeriodMillis,
                   int awaitingDumpedPackets);

        /*!
        Get the percentage of the total traffic that passed between a source and destination Device
        \param source The source Device
        \param destination The destination Device
        \return Not actually a percentage but rather a fraction - easier to work with
        */
        double getTrafficPercentage(shared_ptr<Device> source, shared_ptr<Device> destination);


        /*!
        Get the table of traffic containing percentages. The percentages are calculated as a percetage of
        the total amount of packets being routed
        \param A table of the traffic percentages as a QMap
        */
        shared_ptr<QMap<shared_ptr<Device>,QMap<shared_ptr<Device>,double> > > getTrafficPercentageTable();

        /*!
        Get the table of traffic containing amount of packets

        \param A table of the amount of packets as a QMap
        */
        shared_ptr<QMap<shared_ptr<Device>,QMap<shared_ptr<Device>,double> > > getTrafficAmtPacketsTable();

        /* !
        Get the total amount of packets that were routed in a specified time period
        \return The total amount of packets
        */
        //int getTotalPackets() const;

        /*!
        Get the rate of packets per second according to the specified time period.

        \return The rate in packets/sec
        */
        double getPacketsPerSecond();

        /*!
        Get the rate of bytes per second according to the specified time period.

        \return The rate in bytes/sec
        */
        double getBytesPerSecond();

        /*!
        Get the amount of packets waiting to be written to file by the PacketDumper

        \return The amount of packets waiting to be written to file by the PacketDumper
        */
        int getAwaitingDumpedPackets();

    private:

        shared_ptr<QMap<shared_ptr<Device>,QMap<shared_ptr<Device>,double> > > _percentageTraffic; //!The matrix indicating the percentage of traffic between each network Device
        shared_ptr<QMap<shared_ptr<Device>,QMap<shared_ptr<Device>,double> > > _amtPacketsTraffic; //!The matrix indicating the traffic (in amount of packets) between each network Device
        //int _totalPackets; // !The total amount of packets routed in a specific time period
        double _packetsPerSecond; //!The rate of packets/sec for a given time period
        double _bytesPerSecond; //!The rate of bytes/sec for a given time period
        int _awaitingDumpedPackets; //!The amount of packets waiting to be written to file by the PacketDumper

        /*!
        Generate the matrix of traffic percentages
        \param traffic A matrix of signifying the amount of packets flowing between each of the
        network Devices in a specified time period
        \param totalPackets The total amount of packets routed in the predefined period
        */
        void calculateTrafficPercentage(shared_ptr<QMap<shared_ptr<Device>,QMap<shared_ptr<Device>,double> > >& traffic,
                                        unsigned int totalPackets);

        /*!
        Calculate the different rates associated with the statistics
        \param totalPackets The total amount of packets routed in the predefined period
        \param totalBytes The total amount of bytes routed in the predefined period
        \param timePeriodMillis The amount of time in milliseconds over which to calculate the rates
        */
        void calculateRates(unsigned int totalPackets,unsigned int totalBytes,unsigned int timePeriodMillis);
};

#endif // __STATISTICS_HH__
