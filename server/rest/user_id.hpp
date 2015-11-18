#ifndef USER_Id_HPP_INCLUDED
#define USER_Id_HPP_INCLUDED

#include <cstdint>

namespace Factorem { namespace Server { namespace RestApi {

    struct UserIdHasher;

    class UserId
    {
        friend UserIdHasher;

    public:
        UserId(uint64_t id);
        uint64_t getId();

        bool operator==(UserId const& other) const;

    private:
        uint64_t id_;
    };

    struct UserIdHasher
    {
        std::size_t operator()(UserId const& id) const;
    };

} // namespace RestApi
} // namespace Server
} // namespace Factorem

#endif // USER_Id_HPP_INCLUDED
