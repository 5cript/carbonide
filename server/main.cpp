#include <iostream>

#include "rest/server.hpp"
#include "rest/connection.hpp"
#include "rest/mime.hpp"

#include <fstream>

int main()
{
    using namespace Carbonide::Server::RestApi;

    RestServer server([](std::shared_ptr <RestConnection> connection) {
        //auto& stream = connection->getStream();

        std::ofstream file ("./test.bmp", std::ios_base::binary);

        std::cout << connection->getAddress() << ":" << connection->getPort() << "\n";

        connection->readStream(file);

        connection->sendFile("C:/Users/Tim/Desktop/September.pdf", true);


    }, [](std::shared_ptr <RestConnection> connection, InvalidRequest const& erroneousRequest) {

        ResponseHeader response;
        response.responseCode = 400;
        response.responseString = "Bad Request";
        connection->sendHeader(response);

        std::cerr << erroneousRequest.what() << "\n";
    }, 8081);

    server.start();

    std::cin.get();

    server.stop();

    return 0;
}
