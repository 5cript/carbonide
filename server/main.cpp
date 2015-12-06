#include "api.hpp"

#include <fstream>
#include <iostream>

int main()
{
    using namespace Carbonide::Server;

    sqlpp::sqlite3::connection_config dbConfig;
    dbConfig.path_to_database = "./database.db";
    dbConfig.flags = SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE;
    dbConfig.debug = true;

    Rest::InterfaceProvider restServer(8081);
    Database::SqliteDatabase database(dbConfig);

    ApiSetup <Database::SqliteDatabase> api(&restServer, &database);

    api.setup();
    api.start();

    std::cin.get();
    return 0;
}
