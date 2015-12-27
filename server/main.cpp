#include "server.hpp"

#include "database/tables/user.hpp"
#include "database/tables/base/table_create.hpp"

#include <fstream>
#include <iostream>

int main()
{
    using namespace Carbonide::Server;

    /*
    // database config
    Database::DatabaseConfig dbConfig;
    dbConfig.user = "admin";
    dbConfig.password = "admin";

    // rest, database, api
    Rest::InterfaceProvider restServer(8081);
    Database::Database database;
    CarbonideServer server(&restServer, &database);

    // setup
    server.setup();

    // start
    database.connect(dbConfig);
    restServer.start();

    */

    Database::Tables::createTableQuery <Database::Tables::User>(std::cout);

    //std::cout << "server started on 8081\n";

    std::cin.get();
    return 0;
}
