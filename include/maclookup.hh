#ifndef __MACLOOKUP_HH__
#define __MACLOOKUP_HH__

#include <QMap>
#include <QPair>

#include "ethernetiiframe.hh"

#include "device.hh"

/*!
A MAC address lookup table used by the switch.

\author Simon Jagoe
*/
class MACLookup
{
    public:
        /*!
        Set the Life Time of entries in the table to be the default.
        */
        MACLookup()
        {
            _aliveTime = DEFAULT_ALIVE_TIME;
        };

        /*!
        Add or update entries.

        \param mac The mac address key to add/update
        \param device The device that the client with specified mac is connected to.
        */
        void addEntry( const mac_t& mac, const shared_ptr<Device>& device );

        /*!
        Return the Device that a particular client is connected to, or an empty
        shared_ptr is the client is unknown.

        \param mac Client to look up.
        \return Device that the client is connected to
        */
        shared_ptr<Device> lookupEntry( const mac_t& mac );

    public slots:
        /*!
        Slot that updates the life times in the table.

        \param secondsElapsed Time to subtract from the life time.
        */
        void updateTime(const int& millisecondsElapsed);

    private:
        QMap<mac_t, QPair<shared_ptr<Device>, long> > _lookupTable; //! lookup table to get Device from mac_t.
        long _aliveTime; //! time that an entry will remain in the table (milliseconds)
        static const int DEFAULT_ALIVE_TIME = 90000; //! default time an entry is in the table (milliseconds)
};

#endif
