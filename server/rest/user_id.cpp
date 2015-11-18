#include "user_Id.hpp"

#include <functional>

namespace Factorem { namespace Server { namespace RestApi {
//#######################################################################################################
    UserId::UserId(uint64_t id)
        : id_(id)
    {
    }
//-------------------------------------------------------------------------------------------------------
    bool UserId::operator==(UserId const& other) const
    {
        return other.id_ == id_;
    }
//-------------------------------------------------------------------------------------------------------
    std::size_t UserIdHasher::operator()(UserId const& id) const
    {
        return std::hash <decltype(id.id_)> ()(id.id_);
    }
//#######################################################################################################
} // namespace RestApi
} // namespace Server
} // namespace Factorem
