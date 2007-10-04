#ifndef __STATISTICSLAYER_HH__
#define __STATISTICSLAYER_HH__

#include <QtCore>
#include <QMap>
#include <string>
#include <sstream>

#include <boost/weak_ptr.hpp>

#include "alstatisticslistener.hh"
#include "lockablequeue.hh"

using std::string;
using std::ostringstream;
using boost::weak_ptr;

class Statistics;
class RawPacket;
class PacketDumper;

/*!
A class used to process the statistics with regards to packets being processed by the
Sttyciar software. This class handles signals to update the statistics.

\author Doron Horwitz
*/
class StatisticsLayer: public QThread, public ALStatisticsListener
{
    Q_OBJECT

    public:
        /*!
        Constructor takes currently activated devices from which the StatisticsLayer
        should take statistics

        \param activatedDevices A QList of the all the devices which are contributing statistics
        */
        StatisticsLayer(QList<shared_ptr<Device> >& activatedDevices, weak_ptr<PacketDumper>& dumper);

        /*!
        Add a raw packet to the statistics layer's queue for processsing
        \param rawPacket The packet that is being routed
        */
        void addRawPacket(const shared_ptr<RawPacket>& rawPacket);

        /*!
        Reset the amount of traffic that has flowed between each Device to zero, in order to
        allow for statistics to be used in windowed time periods
        */
        void reset();

        /*!
        Get a string representation of the traffix matrix

        \return The string representation
        */
        string toString();

        /*!
        Stop the processing of packets in the StatisticsLayer
        */
        void stopRunning();

    protected:
        void run();

    private:
        shared_ptr<QMap<shared_ptr<Device>, QMap<shared_ptr<Device>, double> > > _traffic; //!The matrix indicating the percentage of traffic between each network Device
        unsigned int _totalPackets;//!The total amount of packets routed in a specific time period
        unsigned int _totalBytes; //!The total amount of bytes routed in a specific time period
        LockableQueue<shared_ptr<RawPacket> > _statisticsQueue; //!A queue of rawpackets awaiting processing by the statistics layer
        bool _running; //!A flag used by the loop in the run() function to indicate that the thread must continue running. Can be made false using PcapReceiveThread::stopRunning()
        QWaitCondition _waitCondition; //!Used to prevent deadlocks and other concurrent programming problems
        QMutex _waitMutex; //!Use to make the statistics layer sleep if there are no raw packets waiting to be processed
        QMutex _threadSafeMutex; //!Used to prevent deadlocks and other concurrent programming problems

        weak_ptr<PacketDumper> _packetDumper; //! pointer to an object that dumps packets to file

        /*!
        Set up the traffic matrix
        */
        void initializeTable(const QList<shared_ptr<Device> >& activatedDevices);

        /*!
        Update the statistics using the latest routed packet
        \param rawPacket The packet that is being routed
        */
        void updateStatistics(const shared_ptr<RawPacket>& rawPacket);

    public slots:
        /*!
        A Qt slot which the StatisticsLayer uses to perform calculations on the statistics when required
        by an outside object. This slot usually does the calculation and then emits a StatisticsLayer::sendStats(shared_ptr<Statistics>&) signal

        \param timePeriodMillis The amount of milliseconds to use in calculations of rates and other time dependent calculations
        */
        void calculate(int timePeriodMillis);

    signals:
        /*!
        A Qt signal used to update the GUI with the latest statistics

        \param statistics The latest statistics for a given time period
        */
        void sendStats(shared_ptr<Statistics>& statistics);
};

#endif
