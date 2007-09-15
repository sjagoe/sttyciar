#include "exceptions.hh"

DeviceNotFoundException::DeviceNotFoundException(const string& what_arg) : runtime_error(what_arg)
{
}

CannotOpenDeviceException::CannotOpenDeviceException(const string& what_arg) : runtime_error(what_arg)
{
}
