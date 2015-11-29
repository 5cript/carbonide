#include "io_service_provider.hpp"

namespace Carbonide { namespace Server {

    IOServiceProvider::IOServiceProvider()
        : ioService()
    {
    }

    boost::asio::io_service& IOServiceProvider::getIOService()
    {
        return ioService;
    }

} // namespace Server
} // namespace Carbonide
