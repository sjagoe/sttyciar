#include "exceptions.hh"

DeviceNotFoundException::DeviceNotFoundException(const string& what_arg) : runtime_error(what_arg)
{
}
