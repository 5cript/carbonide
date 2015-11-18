#include "server.hpp"
#include "io_service_provider.hpp"
#include "connection.hpp"

using namespace boost::asio::ip;

namespace Factorem { namespace Server { namespace RestApi
{
//#######################################################################################################
    RestServer::RestServer(std::function <void(std::shared_ptr <RestConnection>)> handler, uint16_t port)
        : endpoint_(tcp::v4(), port)
        , acceptor_(nullptr)
        , handler_(handler)
        , acceptingThread_()
        , listening_(false)
        , idIncrement_(0)
        , memberLock_()
        , connections_()
    {

    }
//-------------------------------------------------------------------------------------------------------
    RestServer::~RestServer()
    {
        if (acceptingThread_.joinable())
            stop();
    }
//-------------------------------------------------------------------------------------------------------
    void RestServer::start()
    {
        acceptor_.reset(new tcp::acceptor(IOServiceProvider::getInstance().getIOService(), endpoint_));

        // is currently running, stop first
        if (acceptingThread_.joinable())
            stop();

        listening_.store(true);
        acceptingThread_ = std::thread([this]() {
            for (;listening_.load();)
            {
                idIncrement_.store(idIncrement_.load() + 1);
                std::shared_ptr <RestConnection> connection (new RestConnection(this, idIncrement_.load()));
                boost::system::error_code ec;
                acceptor_->accept(*connection->getStream().rdbuf(), ec);
                if (!ec) {
                    // LOCK_SCOPE
                    {
                        std::lock_guard <std::mutex> guard (memberLock_);
                        connections_.insert({connection->getId(), connection});
                    }
                    std::thread([connection, this](){handler_(connection);}).detach();
                }
            }
        });
    }
//-------------------------------------------------------------------------------------------------------
    void RestServer::stop()
    {
        if (acceptingThread_.joinable());
            acceptingThread_.join();
        acceptor_.reset();
        listening_.store(false);
    }
//-------------------------------------------------------------------------------------------------------
    void RestServer::deregisterClient(RestConnection* connection)
    {
        std::lock_guard <std::mutex> guard (memberLock_);

        connections_.erase(connection->getId());
    }
//#######################################################################################################
} // namespace RestApi
} // namespace Server
} // namespace Factorems
