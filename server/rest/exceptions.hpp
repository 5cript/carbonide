#ifndef EXCEPTIONS_HPP_INCLUDED
#define EXCEPTIONS_HPP_INCLUDED

#include <exception>
#include <stdexcept>
#include <string>

namespace Carbonide { namespace Server { namespace RestApi {

    /**
     *  A RestServer Exception.
     *  All RestServer Exceptions extend this one.
     */
    class RestException : public std::exception
    {
    public:
        RestException(std::string message);
        virtual const char* what() const noexcept;

    private:
        std::string message_;
    };

    /**
     *  An InvalidRequest Exception.
     *  This one is thrown whenever an invalid request has been received.
     *  This usually means a faulty http header or being no http request at all.
     */
    class InvalidRequest : public RestException
    {
    public:
        InvalidRequest(std::string message);
    };

} // namespace RestApi
} // namespace Server
} // namespace Carbonide

#endif // EXCEPTIONS_HPP_INCLUDED
