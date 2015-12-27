#ifndef API_HPP_INCLUDED
#define API_HPP_INCLUDED

#include "../lib/SimpleREST/restful.hpp"
#include "database.hpp"

#include <mutex>

namespace Carbonide { namespace Server {

    class CarbonideServer
    {
    public:
        CarbonideServer(Rest::InterfaceProvider* app, Database::Database* database);

        /**
         *  Registers all RESTful Service calls and prepares all statements.
         */
        void setup();

    private:
        Rest::InterfaceProvider* app_;
        Database::Database* database_;

        std::once_flag setupLock_;
    };
} // namespace Server
} // namespace Carbonide

#endif // API_HPP_INCLUDED
