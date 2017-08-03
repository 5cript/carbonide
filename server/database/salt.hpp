#pragma once

#include <string>

namespace Carbonide { namespace Server {
    std::string generateSalt(std::string::size_type length);
}
}
