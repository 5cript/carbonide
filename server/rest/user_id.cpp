#include "user_Id.hpp"

#include <functional>

namespace Carbonide { namespace Server { namespace RestApi {
//#######################################################################################################
    UserId::UserId(uint64_t id)
        : id_(id)
    {
    }
//-------------------------------------------------------------------------------------------------------
    uint64_t UserId::getId()
    {
        return id_;
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
} // namespace Carbonide
