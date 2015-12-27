#include "database.hpp"

#include <sstream>

namespace Carbonide { namespace Server { namespace Database {
    using namespace soci;
//#######################################################################################################
    Database::Database()
        : session_(nullptr)
    {

    }
//-------------------------------------------------------------------------------------------------------
    void Database::connect(DatabaseConfig const& config)
    {
        std::stringstream sessionCreation;

        // db
        if (config.database)
            sessionCreation << "db='" << config.database.get() << "' ";
        else
            sessionCreation << "db=carbonide ";

        // host
        if (config.host)
            sessionCreation << "host=" << config.host.get() << " ";

        // port
        if (config.port)
            sessionCreation << "port=" << config.port.get() << " ";

        // charset
        if (config.charset)
            sessionCreation << "charset=" << config.charset.get() << " ";

        // user
        sessionCreation << "user='" << config.user << "' ";

        // password
        sessionCreation << "password='" << config.password << "'";

        session_.reset(new session(mysql, sessionCreation.str()));
    }
//-------------------------------------------------------------------------------------------------------
    void Database::disconnect()
    {
        session_.reset(nullptr);
    }
//#######################################################################################################
} // namespace Database
} // namespace Server
} // namespace Carbonide
