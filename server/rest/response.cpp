#include "response.hpp"

#include <sstream>

namespace Carbonide { namespace Server { namespace RestApi
{
//#######################################################################################################
    std::string ResponseHeader::toString() const
    {
        std::stringstream builder;
        builder << httpVersion << " " << responseCode << " " << responseString << "\r\n";
        for (auto const& i : responseHeaderPairs) {
            builder << i.first << ": " << i.second << "\r\n";
        }
        builder << "\r\n";

        return builder.str();
    }
//-------------------------------------------------------------------------------------------------------
    std::string& ResponseHeader::operator[](std::string const& key)
    {
        return responseHeaderPairs[key];
    }
//#######################################################################################################
} // namespace RestApi
} // namespace Server
} // namespace Carbonide
