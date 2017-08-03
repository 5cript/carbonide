#include "session_storage.hpp"
#include "../database/tables/session.hpp"

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
        return "";
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
    void Database::setupSessionStatements()
    {
        using namespace Tables;
        using namespace TableCesdl;

        statements_.insert({"session/create", sql_->prepare << ""});
        statements_.insert({"session/clear", sql_->prepare << ""});
        statements_.insert({"session/count", sql_->prepare << ""});
        statements_.insert({"session/remove", sql_->prepare << ""});
        statements_.insert({"session/get", sql_->prepare << ""});
        statements_.insert({"session/update", sql_->prepare << ""});
    }
//#####################################################################################################################
} // namespace Database
} // namespace Server
} // namespace Carbonide
