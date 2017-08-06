#include "session_storage.hpp"
#include "../database/tables/session.hpp"

#include <table-cedsl/insert_into.hpp>
#include <attender/attender/session/uuid_session_cookie_generator.hpp>

namespace Carbonide { namespace Server { namespace Database
{
//#####################################################################################################################
    SessionStorage::SessionStorage(Database* database)
        : database_{database}
    {
        /// TODO
    }
//---------------------------------------------------------------------------------------------------------------------
    void SessionStorage::clear()
    {
        /// TODO
    }
//---------------------------------------------------------------------------------------------------------------------
    uint64_t SessionStorage::size()
    {
        /// TODO
        return 0;
    }
//---------------------------------------------------------------------------------------------------------------------
    std::string SessionStorage::create_session()
    {
        /// TODO
        auto uuid = attender::uuid_generator::generate_id();
    }
//---------------------------------------------------------------------------------------------------------------------
    void SessionStorage::delete_session(std::string const& id)
    {
        /// TODO
    }
//---------------------------------------------------------------------------------------------------------------------
    bool SessionStorage::get_session(std::string const& id, attender::session& session)
    {
        /// TODO
        return false;
    }
//---------------------------------------------------------------------------------------------------------------------
    bool SessionStorage::set_session(std::string const& id, attender::session const& session)
    {
        /// TODO
        return false;
    }
//#####################################################################################################################
} // namespace Database
} // namespace Server
} // namespace Carbonide
