#include <iostream>

#include "rest/server.hpp"
#include "rest/connection.hpp"
#include "rest/mime.hpp"

int main()
{
    using namespace Carbonide::Server::RestApi;

    RestServer server([](std::shared_ptr <RestConnection> connection) {
        //auto& stream = connection->getStream();

        ResponseHeader response;
        //response["Content-Type"] = "text/plain; charset=UTF-8";
        //response["Content-Type"] = "application/octet-stream";
        // response["Content-Type"] = extensionToMimeType(".pdf");
        connection->sendFile("C:/Users/Tim/Desktop/September.pdf", true, response);

        /*
        auto req = connection->getRequest();
        auto head = connection->getHeader();

        std::cout << req.requestType << "\n";
        std::cout << req.httpVersion << "\n";
        std::cout << req.url << "\n\n";

        for (auto const& i : head.entries)
            std::cout << i.first << ": " << i.second << "\n";
        std::cout << "\n";
        */
    }, [](std::shared_ptr <RestConnection> connection, InvalidRequest const& erroneousRequest) {

        auto& stream = connection->getStream();
        stream << "HTTP/1.1 400 Bad request\r\n";

        std::cerr << erroneousRequest.what() << "\n";
    }, 8081);

    server.start();

    std::cin.get();

    server.stop();

    return 0;
}
