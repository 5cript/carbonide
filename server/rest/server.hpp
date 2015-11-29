#ifndef REST_SERVER_HPP_INCLUDED
#define REST_SERVER_HPP_INCLUDED

#include "forward.hpp"
#include "user_id.hpp"
#include "exceptions.hpp"

#include <boost/asio.hpp>

#include <functional>
#include <unordered_map>
#include <memory>
#include <thread>
#include <mutex>
#include <atomic>

namespace Carbonide { namespace Server { namespace RestApi {

    /**
     *  A RESTful web service server. Provide a callback function which is called when a http request is made.
     */
    class RestServer
    {
        friend RestConnection;

    public:
        /**
         *  Constructs the RestServer, does not automatically bind.
         *
         *  @param handler A handler called when a request has been recieved.
         *         The connection is automatically closed when the function ends.
         *         You can use the connections stream to write a response.
         *
         *  @param errorHandler A handler called when a request is bad.
         *
         *  @param port The port to bind on.
         */
        RestServer(std::function <void(std::shared_ptr <RestConnection>)> handler,
                   std::function <void(std::shared_ptr <RestConnection>, InvalidRequest const&)> errorHandler, uint16_t port = 80);

        /**
         *  Deconstructor. Automatically destroys all connections. Beware!
         *  Never keep any spare shared_ptrs to RestConnections.
         */
        ~RestServer();

        /**
         *  Starts the server and binds to the port. May throw if the socket
         *  cannot be bound to any interface.
         */
        void start();

        /**
         *  Stops the server. Please make sure to finish off all clients or this might lead to std::terminate.
         */
        void stop();

    private:
        /**
         *  called by connection to deregister itself.
         */
        void deregisterClient(RestConnection* connection);

    private:
        boost::asio::ip::tcp::endpoint endpoint_; // socket endpoint
        std::unique_ptr <boost::asio::ip::tcp::acceptor> acceptor_; // acceptor accepting connections

        std::function <void(std::shared_ptr <RestConnection>)> handler_; // handler callback for connections.
        std::function <void(std::shared_ptr <RestConnection>, InvalidRequest const&)> errorHandler_; // handler for invalid requests.

        std::thread acceptingThread_; // acceptor thread
        std::atomic_bool listening_; // listening flag = server is bound?
        std::atomic <uint64_t> idIncrement_; // auto increment for ids. overflow is only an issue if the first connections still exists after 256**8 connections have gone through.
        std::mutex memberLock_; // thread protection

        std::unordered_map <UserId, std::shared_ptr <RestConnection>, UserIdHasher> connections_; // all currently connected peers.
    };

} // namespace RestApi
} // namespace Server
} // namespace Carbonide

#endif // REST_SERVER_HPP_INCLUDED
