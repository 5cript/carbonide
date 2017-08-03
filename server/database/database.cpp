#include "database.hpp"

// tables
#include "tables/user.hpp"

// table utility
#include <table-cedsl/table_create.hpp>
#include <table-cedsl/insert_into.hpp>

// cleanup table creation macros
#include <table-cedsl/undef_cleanup.hpp>

// salt and password
#include "salt.hpp"
#include <openssl/sha.h>

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
        setupStatements();
    }
//-------------------------------------------------------------------------------------------------------
    soci::statement* Database::getStatement(std::string const& name)
    {
        auto iter = statements_.find(name);
        if (iter == std::end(statements_))
            throw std::runtime_error("statement not found");
        return &iter->second;
    }
//-------------------------------------------------------------------------------------------------------
    void Database::setupStatements()
    {
        setupUserStatements();
        setupSessionStatements();
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

        // User
        sql << TableCesdl::createTableQuery <Users> (true, true);
    }
//-------------------------------------------------------------------------------------------------------
    void Database::setupUserStatements()
    {
        using namespace Tables;
        using namespace TableCesdl;

        statements_.insert({"user/add", sql_->prepare << TableCesdl::insertIntoQuery <Users>()});
    }
//-------------------------------------------------------------------------------------------------------
//  void Database::setupSessionStatements() -> session/session_storage.cpp
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
    void Database::addUser(std::string const& name, std::string const& passHashOnce)
    {
        std::string salt = generateSalt(32);
        auto secondLevelHash = generateSecondLevelHash(name, passHashOnce, salt);
    }
//#######################################################################################################
} // namespace Database
} // namespace Server
} // namespace Carbonide
