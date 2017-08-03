#include "server.hpp"

namespace Carbonide { namespace Server
{
//#######################################################################################################
    CarbonideServer::CarbonideServer(boost::asio::io_service* service, Database::Database* database)
        : app_(service, [this](auto* connection, auto ec, auto const& exc) {
            onError(static_cast <attender::tcp_connection*> (connection), ec, exc);
          })
        , database_(database)
    {

    }
//-------------------------------------------------------------------------------------------------------
    void CarbonideServer::onError(attender::tcp_connection* connection, boost::system::error_code ec, std::exception const& exc)
    {

    }
//-------------------------------------------------------------------------------------------------------
    void CarbonideServer::setup()
    {
        std::call_once(setupLock_, [&, this]
        {
            setupUserCalls();
            setupWebInterface();
        });
    }
//-------------------------------------------------------------------------------------------------------
    void CarbonideServer::start(std::string const& port)
    {
        app_.start(port);
    }
//#######################################################################################################
} // namespace Server
} // namespace Carbonide
