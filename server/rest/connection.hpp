#ifndef CONNECTION_HPP_INCLUDED
#define CONNECTION_HPP_INCLUDED

#include "user_id.hpp"
#include "forward.hpp"

#include <memory>
#include <boost/asio.hpp>

namespace Factorem { namespace Server { namespace RestApi {

    class RestConnection : public std::enable_shared_from_this <RestConnection>
    {
    public:
        RestConnection(RestServer* owner, UserId const& id);
        ~RestConnection() = default;

        void free();
        boost::asio::ip::tcp::iostream& getStream();
        UserId getId() const;

    private:
        RestServer* owner_;
        boost::asio::ip::tcp::iostream stream_;
        UserId id_;
    };

} // namespace RestApi
} // namespace Server
} // namespace Factorem


#endif // CONNECTION_HPP_INCLUDED
