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
            // interface
            app_.get("/test", [](auto req, auto res)
            {
                res->status(200).send("Hello");
            });

            app_.get("/add_user/:name", [this](auto req, auto res)
            {
                res->send_status(200);
            });
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
