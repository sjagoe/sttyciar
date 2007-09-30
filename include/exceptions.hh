#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <stdexcept>

using namespace std;

/*!
An exception to indicate that no devices can be found by libpcap

\author Doron Horwitz
*/
class DeviceNotFoundException : public runtime_error
{
    public:
        /*!
        Constructor

        \param what_arg A string description of the error that occured
        */
        DeviceNotFoundException(const string& what_arg);
};

/*!
An exception to indicate that a device cannot be opened by libpcap to send and receive packets

\author Doron Horwitz
*/
class CannotOpenDeviceException : public runtime_error
{
    public:
        /*!
        Constructor

        \param what_arg A string description of the error that occured
        */
        CannotOpenDeviceException(const string& what_arg);
};

#endif // EXCEPTIONS_H
