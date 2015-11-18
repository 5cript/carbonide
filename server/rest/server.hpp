#ifndef REST_SERVER_HPP_INCLUDED
#define REST_SERVER_HPP_INCLUDED

#include "forward.hpp"
#include "user_id.hpp"

#include <boost/asio.hpp>

#include <functional>
#include <unordered_map>
#include <memory>
#include <thread>
#include <mutex>
#include <atomic>

namespace Factorem { namespace Server { namespace RestApi {

    class RestServer
    {
        friend RestConnection;

    public:
        RestServer(std::function <void(std::shared_ptr <RestConnection>)> handler, uint16_t port = 80);
        ~RestServer();

        void start();
        void stop();

    private:
        void deregisterClient(RestConnection* connection);

    private:
        boost::asio::ip::tcp::endpoint endpoint_;
        std::unique_ptr <boost::asio::ip::tcp::acceptor> acceptor_;

        std::function <void(std::shared_ptr <RestConnection>)> handler_;
        std::thread acceptingThread_;
        std::atomic_bool listening_;
        std::atomic <uint64_t> idIncrement_;
        std::mutex memberLock_;

        std::unordered_map <UserId, std::shared_ptr <RestConnection>, UserIdHasher> connections_;
    };

} // namespace RestApi
} // namespace Server
} // namespace Factorem

#endif // REST_SERVER_HPP_INCLUDED
