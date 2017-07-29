#include "server.hpp"

#include <fstream>
#include <iostream>

int main()
{
    using namespace Carbonide::Server;

    // database config
    Database::DatabaseConfig dbConfig;
    dbConfig.user = "admin";
    dbConfig.password = "admin";

    // rest, database, api
    //Rest::InterfaceProvider restServer(8081);
    Database::Database database;
    CarbonideServer server(&database);

    // setup
    server.setup();

    // start
    database.connect(dbConfig);

    database.setupTables();

    //restServer.start();

    // Database::Tables::createTableQuery <Database::Tables::User>(std::cout);

    //std::cout << "server started on 8081\n";

    std::cin.get();
    return 0;
}
