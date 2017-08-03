#include "server.hpp"

#include <fstream>
#include <iostream>

int main()
{
    using namespace Carbonide::Server;

    // database config
    Database::DatabaseConfig dbConfig;
    dbConfig.backend = "sqlite3";
    dbConfig.dbName = "carbonide.sqlite3";
    dbConfig.user = "admin";
    dbConfig.password = "admin";

    // database setup
    Database::Database database{dbConfig};
    database.connect();
    database.setup();

    // rest api
    attender::managed_io_context <attender::thread_pooler> context;
    CarbonideServer server(context.get_io_service(), &database);

    // setup
    server.setup();

    // start
    server.start("8081");

    //std::cout << "server started on 8081\n";

    std::cin.get();
    return 0;
}
