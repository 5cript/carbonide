#ifndef IO_SERVICE_PROVIDER_HPP_INCLUDED
#define IO_SERVICE_PROVIDER_HPP_INCLUDED

#include <memory>
#include <boost/asio.hpp>

namespace Carbonide { namespace Server {

    /**
     *  A boost::asio::io_service provider.
     *  The io service used is a global variable and therefore
     *  wrapped in a singleton.
     *
     *  This class might provide thread pooling in the future.
     */
    class IOServiceProvider
    {
    public:
        // concopyable
        ~IOServiceProvider() = default;
        IOServiceProvider(IOServiceProvider const&) = delete;
        IOServiceProvider& operator=(IOServiceProvider const&) = delete;

        /**
        *   Singleton getInstance
        */
        static IOServiceProvider& getInstance() {
            static IOServiceProvider provider;
            return provider;
        }

        /**
         *  Returns boost::asio::io_service.
         */
        boost::asio::io_service& getIOService();

    private:
        IOServiceProvider(); // not constructible
        boost::asio::io_service ioService; // io_service
    };

} // namespace Server
} // namespace Carbonide

#endif // IO_SERVICE_PROVIDER_HPP_INCLUDED
