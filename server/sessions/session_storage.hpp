#pragma once

#include "../database/database_friends.hpp"
#include "../database.hpp"

#include <attender/attender/session/session_storage_interface.hpp>
#include <attender/attender/session/session.hpp>

namespace Carbonide { namespace Server { namespace Database
{
    class SessionStorage : public attender::session_storage_interface
    {
        public:
            SessionStorage(Database* database);

            void clear() override;
            uint64_t size() override;
            std::string create_session() override;
            void delete_session(std::string const& id) override;
            bool get_session(std::string const& id, attender::session& session) override;
            bool set_session(std::string const& id, attender::session const& session) override;

        private:
            Database* database_;
    };
} // namespace Database
} // namespace Server
} // namespace Carbonide
