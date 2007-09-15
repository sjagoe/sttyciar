#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <stdexcept>

using namespace std;

class DeviceNotFoundException : public runtime_error
{
    public:
        DeviceNotFoundException(const string& what_arg);
};

class CannotOpenDeviceException : public runtime_error
{
    public:
        CannotOpenDeviceException(const string& what_arg);
};

#endif // EXCEPTIONS_H
