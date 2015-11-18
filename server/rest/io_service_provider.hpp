#ifndef IO_SERVICE_PROVIDER_HPP_INCLUDED
#define IO_SERVICE_PROVIDER_HPP_INCLUDED

#include <memory>
#include <boost/asio.hpp>

namespace Factorem { namespace Server {

    class IOServiceProvider
    {
    public:
        ~IOServiceProvider() = default;
        IOServiceProvider(IOServiceProvider const&) = delete;
        IOServiceProvider& operator=(IOServiceProvider const&) = delete;

        static IOServiceProvider& getInstance() {
            static IOServiceProvider provider;
            return provider;
        }

        boost::asio::io_service& getIOService();

    private:
        IOServiceProvider();
        boost::asio::io_service ioService;
    };

} // namespace Server
} // namespace Factorem

#endif // IO_SERVICE_PROVIDER_HPP_INCLUDED
