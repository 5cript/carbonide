#include "database.hpp"

// table utility
#include <table-cedsl/table_create.hpp>

// tables
#include "tables/user.hpp"

// cleanup table creation macros
#include <table-cedsl/undef_cleanup.hpp>

#include <iostream>
#include <sstream>

namespace Carbonide { namespace Server { namespace Database {
    using namespace soci;
    using namespace std::string_literals;
//#######################################################################################################
    Database::Database(DatabaseConfig const& config)
        : sql_(nullptr)
        , config_{config}
    {

    }
//-------------------------------------------------------------------------------------------------------
    void Database::connect()
    {
        std::stringstream sessionCreation;

        sessionCreation << "dbname=" << config_.dbName << " ";

        // host
        if (config_.host)
            sessionCreation << "host=" << config_.host.get() << " ";

        // port
        if (config_.port)
            sessionCreation << "port=" << config_.port.get() << " ";

        // charset
        if (config_.charset)
            sessionCreation << "charset=" << config_.charset.get() << " ";

        // user
        if (config_.user)
            sessionCreation << "user='" << config_.user.get() << "' ";

        // password
        if (config_.password)
            sessionCreation << "password='" << config_.password.get() << "'";

        // new soci::session{config.backend, "dbname="s + config.dbName}
        sql_.reset(new session(config_.backend, sessionCreation.str()));
    }
//-------------------------------------------------------------------------------------------------------
    void Database::setupTables()
    {
        using namespace Tables;
        auto& sql = *sql_;

        sql << TableCesdl::createTableQuery <User> (true, true);
        std::cout << TableCesdl::createTableQuery <User> (true, true) << "\n";
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
