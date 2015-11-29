#ifndef MIME_HPP_INCLUDED
#define MIME_HPP_INCLUDED

#include <string>

namespace Carbonide { namespace Server { namespace RestApi {

    // source: http://www.freeformatter.com/mime-types-list.html
    /**
     *  Converts a file extension to a mime type if known.
     *  @param extension A file extension including dot in front.
     *
     *  @return a MIME type.
     */
    std::string extensionToMimeType(std::string const& extension);

} // namespace RestApi
} // namespace Server
} // namespace Carbonide

#endif // MIME_HPP_INCLUDED
