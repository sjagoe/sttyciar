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

/*!
A class used to process the statistics with regards to packets being processed by the
Sttyciar software. This class handles signals to update the statistics.

\author Doron Horwitz
*/
class StatisticsLayer: public QObject, public ALStatisticsListener
{
    Q_OBJECT

    public:
        /*!
        Default constructor
        */
        StatisticsLayer();

        /*!
        Update the statistics using the latests routed packet
        \param interfaceRoute The InterfaceRoute containing information of how a packet was routed
        */
        void updateStatistics(shared_ptr<InterfaceRoute>& interfaceRoute);

        /*!
        Set up the traffic matrix
        */
        void initializeTable(QList<shared_ptr<Device> >& devices);

        /*!
        Reset the amount of traffic that has flowed between each Device to zero, in order to
        allow for statistics to be used in windowed time periods
        */
        void clearTable();

        /* !

        */
        //shared_ptr<Statistics> getStatistics();

        /*!
        Get a string representation of the traffix matrix

        \return The string representation
        */
        string toString();

    private:
        shared_ptr<QMap<shared_ptr<Device>, QMap<shared_ptr<Device>, double> > > _traffic; //!The matrix indicating the percentage of traffic between each network Device
        int _totalPackets;//!The total amount of packets routed in a specific time period

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
