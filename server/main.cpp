#include <iostream>

#include "rest/server.hpp"
#include "rest/connection.hpp"

int main()
{
    using namespace Factorem::Server::RestApi;

    RestServer server([](std::shared_ptr <RestConnection> connection) {
        auto& stream = connection->getStream();

        std::cout << "Hello dude!" << connection->getId().getId() << "\n";

        stream << "HTTP/1.1 200 OK\r\n";
        stream << "Content-Type: text/html;\r\n";
        stream << "Cache-Control: no-cache";
        stream << "Connection: close";
        stream << "Pragma: no-cache";
        stream << "\r\n\r\n";
        stream << "Hello";
        stream.flush();

        std::cout << "Bye dude!\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(250));

        connection->free();
    }, 8081);

    server.start();

    std::cin.get();

    return 0;
}
