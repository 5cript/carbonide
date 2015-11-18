#include "io_service_provider.hpp"

namespace Factorem { namespace Server {

    IOServiceProvider::IOServiceProvider()
        : ioService()
    {
    }

    boost::asio::io_service& IOServiceProvider::getIOService()
    {
        return ioService;
    }

} // namespace Server
} // namespace Factorem
