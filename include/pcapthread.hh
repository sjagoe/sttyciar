#ifndef __PCAPTHREAD_HH__
#define __PCAPTHREAD_HH__

#include <QtCore>
#include <boost/shared_ptr.hpp>
#include "device.hh"

using boost::shared_ptr;

class PcapThread : public QThread
{
    Q_OBJECT

    public:
        PcapThread();

        PcapThread(const shared_ptr<Device>& device);

        ~PcapThread();

    protected:
        void run();
    private:
        shared_ptr<Device> _device;
};

#endif // PCAPTHREAD_HH
