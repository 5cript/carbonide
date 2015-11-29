#ifndef CONNECTION_HPP_INCLUDED
#define CONNECTION_HPP_INCLUDED

#include "user_id.hpp"
#include "forward.hpp"
#include "request.hpp"
#include "header.hpp"
#include "exceptions.hpp"
#include "response.hpp"

#ifndef Q_MOC_RUN // A Qt workaround, for those of you who use Qt
#   include "../../lib/SimpleJSON/stringify/jss.h"
#   include "../../lib/SimpleJSON/stringify/jss_fusion_adapted_struct.h"
#endif

#include <string>
#include <memory>
#include <boost/asio.hpp>

namespace Carbonide { namespace Server { namespace RestApi {

    /**
     *  A REST connection to a client.
     */
    class RestConnection : public std::enable_shared_from_this <RestConnection>
    {
        friend RestServer;

    public:
        ~RestConnection() = default;

        /**
         *  Returns the socket iostream for writing.
         *  Do not read the header from it.
         *  It is recommended to call flush after writing everything to the stream.
         *
         *  @return A tcp::iostream. See boost asio documentation.
         */
        boost::asio::ip::tcp::iostream& getStream();

        /**
         *  Returns the connected clients id.
         *
         *  @return Returns the user id.
         */
        UserId getId() const;

        /**
         *  Returns the request that has been parsed.
         *
         *  @return A request containing all info present in the first line of a request.
         */
        Request getRequest() const;

        /**
         *  Returns the http header entries.
         *
         *  @return A header containing the key:value pairs.
         */
        Header getHeader() const;

        /**
         *  Returns the size of the body.
         *
         *  @return body size.
         */
        uint32_t getBodySize() const;

        /**
         *  Send JSON response. uses SimpleJSON library to stringify the object.
         *  Automatically sets the following header key/value pairs
         *
         *  Content-Type: text/json; charset=UTF-8
         *  Content-Length: ...
         *  Connection: close
         *
         *  @param object An object to stringify.
         *  @param responseHeader A response header containing header information,
         *         such as response code, version and response message.
         */
        template <typename T>
        void sendJson(T const& object, ResponseHeader response = {})
        {
            using namespace std::literals;

            response.responseHeaderPairs["Content-Type"s] = "text/json; charset=UTF-8"s;

            std::stringstream body;
            body << '{';
            JSON::try_stringify(body, "", object);
            body << '}';

            auto bodySize = body.tellp();
            response.responseHeaderPairs["Content-Length"s] = std::to_string(bodySize);
            response.responseHeaderPairs["Connection"s] = "close"s;

            body.seekg(0);

            stream_ << response.toString();
            stream_ << body.rdbuf();
            stream_.flush();
        }

        /**
         *  Sends a file as content.
         *  The response will be 204 for empty files and whats provided otherwise,
         *  which might be 200 if no explicit response header is provided.
         *  It does not send error codes on itself, but throws when the file cannot be opened.
         *
         *  Automatically sets the following header key/value pairs
         *
         *  Content-Length: ...
         *
         *  @param fileName A file to send.
         *  @param responseHeader A response header containing header information,
         *         such as response code, version and response message.
         */
        void sendFile(std::string const& fileName, bool autoDetectContentType = true, ResponseHeader response = {});

        /**
         *  Sends a string. You must set the content type yourself on the response parameter.
         *  Therefore the parameter is not optional.
         *  The response will be 204 for empty strings and whats provided otherwise,
         *  which might be 200 if no explicit response header is provided.
         *
         *  Automatically sets the following header key/value pairs
         *
         *  Content-Length: text.length()
         *
         *  @param text A text to send.
         *  @param responseHeader A response header containing header information,
         *         such as response code, version and response message.
         */
        void sendString(std::string const& text, ResponseHeader response);

    private:
        /**
         *  Connections can only be created by a server.
         *  Users shall never create a connection on their own,
         *  this makes no sense.
         */
        RestConnection(RestServer* owner, UserId const& id);

        /**
         *  Reads and parses the head.
         */
        void readHead();

        /**
         *  Closes the connection and removes it from the server list.
         */
        void free();

    private:
        RestServer* owner_;
        UserId id_;
        boost::asio::ip::tcp::iostream stream_;

        Request request_;
        Header head_;
        uint32_t bodySize_;
    };

} // namespace RestApi
} // namespace Server
} // namespace Carbonide


#endif // CONNECTION_HPP_INCLUDED
