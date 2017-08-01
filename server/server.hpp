#ifndef API_HPP_INCLUDED
#define API_HPP_INCLUDED

#include "database.hpp"

#include <attender/attender.hpp>

#include <mutex>

namespace Carbonide { namespace Server {

    class CarbonideServer
    {
    public:
        CarbonideServer(boost::asio::io_service* service, Database::Database* database);

        /**
         *  Registers all RESTful Service calls and prepares all statements.
         */
        void setup();

        /**
         *  Start REST server on port.
         */
        void start(std::string const& port);

    private:
        void onError(attender::tcp_connection* connection, boost::system::error_code ec, std::exception const& exc);

    private:
        attender::tcp_server app_;
        Database::Database* database_;

        std::once_flag setupLock_;
    };
} // namespace Server
} // namespace Carbonide

#endif // API_HPP_INCLUDED
