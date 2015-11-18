#include "io_service_provider.hpp"

IOServiceProvider::IOServiceProvider()
    : ioService()
{
}

boost::asio::io_service& IOServiceProvider::getIOService()
{
    return ioService;
}
