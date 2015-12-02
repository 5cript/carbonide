#ifndef CONNECTION_HPP_INCLUDED
#define CONNECTION_HPP_INCLUDED

#include "user_id.hpp"
#include "forward.hpp"
#include "request.hpp"
#include "header.hpp"
#include "exceptions.hpp"
#include "response.hpp"

#ifndef Q_MOC_RUN // A Qt workaround, for those of you who use Qt
#   include "../../lib/SimpleJSON/parse/jsd.h"
#   include "../../lib/SimpleJSON/parse/jsd_convenience.h"
#   include "../../lib/SimpleJSON/stringify/jss.h"
#   include "../../lib/SimpleJSON/stringify/jss_fusion_adapted_struct.h"
#endif

#include <string>
#include <memory>
#include <boost/asio.hpp>
#include <cmath>
#include <chrono>
#include <functional>

namespace Carbonide { namespace Server { namespace RestApi {

    using namespace std::literals;

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
        std::size_t getBodySize() const;

        /**
         *  Returns the remote address.
         *
         *  @return Remote peer address as string.
         */
        std::string getAddress() const;

        /**
         *  Returns the remote endpoints port.
         *
         *  @return Remote peer port.
         */
        uint32_t getPort() const;

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
         *  @param response A response header containing header information,
         *         such as response code, version and response message.
         */
        void sendString(std::string const& text, ResponseHeader response);

        /**
         *  Sends only the header and an empty body.
         *
         *  @param response The header information to send.
         */
        void sendHeader(ResponseHeader response);

        /**
         *  Reads the body as a text string.
         *  Please be aware the reading the stream content reads it all.
         *  We would not recommend to mix data in a single request, use multiple
         *  request or the convenience of JSON.
         *
         *  @return The body.
         */
        std::string readString(std::chrono::duration <long> const& timeout = 3s);

        /**
         *  Reads the socket content to a stream.
         *  This is useful to save the body to a file.
         *  Please be aware the reading the stream content reads it all.
         *  We would not recommend to mix data in a single request, use multiple
         *  request or the convenience of JSON.
         *
         *  @return The passed stream
         */
        std::ostream& readStream(std::ostream& stream, std::chrono::duration <long> const& timeout = 3s);

        /**
         *  Reads the body and tries to parse it as JSON.
         *  Please be aware the reading the stream content reads it all.
         *  We would not recommend to mix data in a single request.
         *
         *  @param object Writes the JSON into this object.
         */
        template <typename T>
        void readJson(T& object, std::chrono::duration <long> const& timeout = 3s)
        {
            auto json = "{content:" + readString(timeout) + "}";
            auto tree = JSON::parse_json(json);
            JSON::parse(object, "content", tree);
        }

        /**
         *  Returns whether or not the body contains any data.
         *
         *  @return bodySize == 0
         */
        bool isBodyEmpty();

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

        /**
         *  Sets the remote endpoint for access.
         */
        void setEndpoint(boost::asio::ip::tcp::acceptor::endpoint_type remote);

        /**
         *  Internal function that reduces code duplication
         */
        void read(std::function <void(char const*, long)> writer, std::chrono::duration <long> const& timeout);

    private:
        RestServer* owner_;
        UserId id_;
        boost::asio::ip::tcp::iostream stream_;
        boost::asio::ip::tcp::acceptor::endpoint_type endpoint_;

        Request request_;
        Header head_;
    };

} // namespace RestApi
} // namespace Server
} // namespace Carbonide


#endif // CONNECTION_HPP_INCLUDED
