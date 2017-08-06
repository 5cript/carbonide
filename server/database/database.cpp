#include "database.hpp"

// tables
#include "tables/user.hpp"
#include "tables/session.hpp"

// table utility
#include <table-cedsl/table_create.hpp>
#include <table-cedsl/insert_into.hpp>

// cleanup table creation macros
#include <table-cedsl/undef_cleanup.hpp>

// salt and password
#include "salt.hpp"
#include <openssl/sha.h>

#include <attender/attender/session/uuid_session_cookie_generator.hpp>

#include <iostream>
#include <sstream>

namespace Carbonide { namespace Server { namespace Database {
    using namespace soci;
    using namespace std::string_literals;
//#######################################################################################################
//#######################################################################################################
    Database::Database(DatabaseConfig const& config)
        : sql_(nullptr)
        , config_{config}
    {

    }
//-------------------------------------------------------------------------------------------------------
    void Database::setup()
    {
        setupTables();
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

        // Creating Tables, if not existant.
        sql << TableCesdl::createTableQuery <Users> (true, true);
        sql << TableCesdl::createTableQuery <Sessions> (true, true);
    }
//-------------------------------------------------------------------------------------------------------
    void Database::disconnect()
    {
        sql_.reset(nullptr);
    }
//-------------------------------------------------------------------------------------------------------
    std::string Database::generateSecondLevelHash(std::string const& name, std::string const& passHashOnce, std::string const& salt)
    {
        std::basic_string <unsigned char> passHashTwice{64};
        std::basic_string <unsigned char> salted;

        for (auto const& i : name)
            salted.push_back((char)i);
        for (auto const& i : passHashOnce)
            salted.push_back((char)i);

        SHA256(salted.c_str(), salted.length(), &*passHashTwice.begin());

        std::string str;
        for (auto const& i : passHashTwice)
            str.push_back((char)i);
        return str;
    }
//-------------------------------------------------------------------------------------------------------
    void Database::addUser(std::string const& email, std::string const& name, std::string const& passHashOnce)
    {
        std::string salt = generateSalt(32);
        auto secondLevelHash = generateSecondLevelHash(name, passHashOnce, salt);

        auto uuid = attender::uuid_generator::generate_id();

        //statement->bind(uuid, email, name, secondLevelHash, salt, std::vector <unsigned char> {});
        //statement->execute();
    }
//#######################################################################################################
} // namespace Database
} // namespace Server
} // namespace Carbonide
