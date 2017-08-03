#pragma once

#include <attender/attender/session/session.hpp>

namespace Carbonide { namespace Server
{
    struct Session : public attender::session
    {
        Session(std::string id = "");
    };
}
}
