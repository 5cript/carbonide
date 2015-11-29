#ifndef RESPONSE_HPP_INCLUDED
#define RESPONSE_HPP_INCLUDED

#include <string>
#include <unordered_map>
#include <cstdint>

namespace Carbonide { namespace Server { namespace RestApi {

    /**
     *  A pure holder for response information.
     */
    struct ResponseHeader
    {
        std::string httpVersion = "HTTP/1.1";
        uint16_t responseCode = 200;
        std::string responseString = "OK";
        std::unordered_map <std::string, std::string> responseHeaderPairs;

        /**
         *  Turns the response header into a conforming header.
         *  Can be prepended to the body.
         *
         *  @return A string representation of this.
         */
        std::string toString() const;

        /**
         *  Shorthand operator for header key value pairs.
         */
        std::string& operator[](std::string const& key);
    };

} // namespace RestApi
} // namespace Server
} // namespace Carbonide


#endif // RESPONSE_HPP_INCLUDED
