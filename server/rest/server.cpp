#include "server.hpp"
#include "io_service_provider.hpp"
#include "connection.hpp"

using namespace boost::asio::ip;

namespace Carbonide { namespace Server { namespace RestApi
{
//#######################################################################################################
    RestServer::RestServer(std::function <void(std::shared_ptr <RestConnection>)> handler,
                           std::function <void(std::shared_ptr <RestConnection>, InvalidRequest const&)> errorHandler, uint16_t port)
        : endpoint_(tcp::v4(), port)
        , acceptor_(nullptr)
        , handler_(handler)
        , errorHandler_(errorHandler)
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
        // running? -> stop!
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
                    std::thread([connection, this](){
                        try {
                            connection->readHead();
                            handler_(connection);
                        } catch (InvalidRequest const& exc) {
                            errorHandler_(connection, exc);
                        }
                        connection->free();
                        //catch (...) {
                        // std::terminate - do not handle unexpected exceptions.
                        // we don't wanna catch our programming errors ;)
                        //}
                    }).detach();
                }
            }
        });
    }
//-------------------------------------------------------------------------------------------------------
    void RestServer::stop()
    {
        // dont touch the ordering. Everything else deadlock
        acceptor_.reset();
        listening_.store(false);

        if (acceptingThread_.joinable());
            acceptingThread_.join();
    }
//-------------------------------------------------------------------------------------------------------
    void RestServer::deregisterClient(RestConnection* connection)
    {
        // remove a client from the list to make it available for deletion.
        std::lock_guard <std::mutex> guard (memberLock_);

        connections_.erase(connection->getId());
    }
//#######################################################################################################
} // namespace RestApi
} // namespace Server
} // namespace Carbonides
