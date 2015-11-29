#include "exceptions.hpp"

namespace Carbonide { namespace Server { namespace RestApi
{
//#######################################################################################################
    RestException::RestException(std::string message)
        : message_(std::move(message))
    {

    }
//-------------------------------------------------------------------------------------------------------
    const char* RestException::what() const noexcept
    {
        return message_.c_str();
    }
//-------------------------------------------------------------------------------------------------------
    InvalidRequest::InvalidRequest(std::string message)
        : RestException(std::move(message))
    {

    }
//#######################################################################################################
} // namespace RestApi
} // namespace Server
} // namespace Carbonide

