#include "connection.hpp"
#include "server.hpp"

namespace Factorem { namespace Server { namespace RestApi
{
//#######################################################################################################
    RestConnection::RestConnection(RestServer* owner, UserId const& id)
        : owner_(owner)
        , id_(id)
    {
    }
//-------------------------------------------------------------------------------------------------------
    void RestConnection::free()
    {
        stream_.close();
        owner_->deregisterClient(this);
    }
//-------------------------------------------------------------------------------------------------------
    boost::asio::ip::tcp::iostream& RestConnection::getStream()
    {
        return stream_;
    }
//-------------------------------------------------------------------------------------------------------
    UserId RestConnection::getId() const
    {
        return id_;
    }
//#######################################################################################################
} // namespace RestApi
} // namespace Server
} // namespace Factorem
