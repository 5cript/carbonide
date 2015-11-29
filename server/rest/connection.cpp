#include "connection.hpp"
#include "server.hpp"

#include <fstream>
#include <stdexcept>
#include <iterator>
#include <algorithm>

namespace Carbonide { namespace Server { namespace RestApi
{
//#######################################################################################################
    uint64_t readFile(std::ifstream& reader, ResponseHeader& response)
    {
        if (!reader.good())
            throw std::runtime_error("Could not open file.");

        reader.seekg(0, reader.end);
        auto size = reader.tellg();
        reader.seekg(0, reader.beg);

        if (size == 0)
        {
            response.responseCode = 204;
            response.responseString = "No Content";
        }

        return size;
    }
//-------------------------------------------------------------------------------------------------------
//#######################################################################################################
    RestConnection::RestConnection(RestServer* owner, UserId const& id)
        : owner_(owner)
        , id_(id)
        , stream_()
        , request_()
        , head_()
        , bodySize_(0)
    {
    }
//-------------------------------------------------------------------------------------------------------
    void RestConnection::free()
    {
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
//-------------------------------------------------------------------------------------------------------
    Request RestConnection::getRequest() const
    {
        return request_;
    }
//-------------------------------------------------------------------------------------------------------
    Header RestConnection::getHeader() const
    {
        return head_;
    }
//-------------------------------------------------------------------------------------------------------
    uint32_t RestConnection::getBodySize() const
    {
        return bodySize_;
    }
//-------------------------------------------------------------------------------------------------------
    void RestConnection::readHead()
    {
        // read first line of request.
        stream_ >> request_.requestType;
        stream_ >> request_.url;
        stream_ >> request_.httpVersion;

        if (!stream_ || request_.httpVersion.substr(0, 5) != "HTTP/")
        {
            throw InvalidRequest("Request does not contain a valid HTTP request header.");
        }

        // validate http version
        //------------------------------------------------------------
        auto version = request_.httpVersion.substr(5, request_.httpVersion.length() - 5);

        if (version != "1.0" && version != "1.1")
            throw InvalidRequest("HTTP version is not supported");
        //------------------------------------------------------------

        // Process the response headers, which are terminated by a blank line.
        std::string headerLine;
        std::getline(stream_, headerLine);
        while (std::getline(stream_, headerLine))
        {
            if (headerLine == "\r")
                break;

            auto pos = headerLine.find(":");
            if (pos == std::string::npos)
                throw InvalidRequest("HTTP header entry does not contain colon");

            auto lhs = headerLine.substr(0, pos);
            auto rhs = headerLine.substr(pos + 1, headerLine.length() - pos);

            head_.entries[lhs] = rhs;
        }

        bodySize_ = stream_.rdbuf()->available();
    }
//-------------------------------------------------------------------------------------------------------
    void RestConnection::sendBinaryFile(std::string const& fileName, ResponseHeader response)
    {
        std::ifstream reader(fileName, std::ios_base::binary);
        auto size = readFile(reader, response);

        //if (!response.isSet("Content-Type"))
        //    response.responseHeaderPairs["Content-Type"] = "application/octet-stream";
        response.responseHeaderPairs["Content-Length"] = std::to_string(size);

        stream_ << response.toString();
        char buffer[65536];
        do {
            reader.read(buffer, 65536);
            stream_.write(buffer, reader.gcount());
        } while (reader.gcount() == 65536);
    }
//-------------------------------------------------------------------------------------------------------
    void RestConnection::sendTextFile(std::string const& fileName, std::string contentType, ResponseHeader response)
    {
        using namespace std::literals;

        std::ifstream reader(fileName, std::ios_base::binary);
        auto size = readFile(reader, response);

        if (!response.isSet("Content-Type"))
            response.responseHeaderPairs["Content-Type"] = "text/"s + contentType;
        response.responseHeaderPairs["Content-Length"] = std::to_string(size);

        stream_ << response.toString();
        char buffer[65536];
        do {
            reader.read(buffer, 65536);
            stream_.write(buffer, reader.gcount());
        } while (reader.gcount() == 65536);
    }
//-------------------------------------------------------------------------------------------------------
    void RestConnection::sendString(std::string const& text, ResponseHeader response)
    {
        response.responseHeaderPairs["Content-Length"] = std::to_string(text.length());

        stream_ << response.toString();
        stream_ << text;
    }
//#######################################################################################################
} // namespace RestApi
} // namespace Server
} // namespace Carbonide
