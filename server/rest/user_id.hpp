#ifndef USER_Id_HPP_INCLUDED
#define USER_Id_HPP_INCLUDED

#include <cstdint>

namespace Carbonide { namespace Server { namespace RestApi {

    struct UserIdHasher;

    /**
     *  A user id is nothing but a number for now.
     *  This might change in the future.
     *
     *  Possible alternatvies: peer addr + port, guid
     */
    class UserId
    {
        friend UserIdHasher;

    public:
        UserId(uint64_t id);

        /**
         *  Returns the user id as a numerical representation.
         *
         *  @return Returns the user id as a numerical representation.
         */
        uint64_t getId();

        bool operator==(UserId const& other) const;

    private:
        uint64_t id_;
    };

    /**
     *  Necessary to used UserId classes as a unordered_map key.
     */
    struct UserIdHasher
    {
        std::size_t operator()(UserId const& id) const;
    };

} // namespace RestApi
} // namespace Server
} // namespace Carbonide

#endif // USER_Id_HPP_INCLUDED
