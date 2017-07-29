#include "database.hpp"

// table utility
#include "tables/base/table_create.hpp"

// tables
#include "tables/user.hpp"

// cleanup table creation macros
#include "tables/base/undef_cleanup.hpp"

#include <iostream>
#include <sstream>

namespace Carbonide { namespace Server { namespace Database {
    using namespace soci;
//#######################################################################################################
    Database::Database()
        : sql_(nullptr)
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

        //sql_.reset(new session(mysql, sessionCreation.str()));
    }
//-------------------------------------------------------------------------------------------------------
    void Database::setupTables()
    {
        using namespace Tables;
        auto& sql = *sql_;

        sql << createTableQuery <User> ();
        std::cout << createTableQuery <User> ();
    }
//-------------------------------------------------------------------------------------------------------
    void Database::disconnect()
    {
        sql_.reset(nullptr);
    }
//#######################################################################################################
} // namespace Database
} // namespace Server
} // namespace Carbonide
