#ifndef DATABASE_DATABASE_HPP_INCLUDED
#define DATABASE_DATABASE_HPP_INCLUDED

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#include <soci/soci.h>
#pragma GCC diagnostic pop

#ifndef Q_MOC_RUN // A Qt workaround, for those of you who use Qt
#   include <SimpleJSON/parse/jsd.hpp>
#   include <SimpleJSON/parse/jsd_convenience.hpp>
#   include <SimpleJSON/stringify/jss.hpp>
#   include <SimpleJSON/stringify/jss_fusion_adapted_struct.hpp>
#endif

#include <unordered_map>
#include <memory>
#include <string>
#include <boost/optional.hpp>

namespace Carbonide { namespace Server { namespace Database {

    struct DatabaseConfig : public JSON::Stringifiable <DatabaseConfig>
                          , public JSON::Parsable <DatabaseConfig>
    {
        std::string backend;
        std::string dbName;
        boost::optional <std::string> user;
        boost::optional <std::string> password;
        boost::optional <std::string> host; // default = localhost
        boost::optional <uint32_t> port; // default = 3306
        boost::optional <std::string> charset;
    };

    class Database
    {
    public:
        Database(DatabaseConfig const& config);

        void connect();
        void disconnect();

        std::string generateSecondLevelHash(std::string const& name, std::string const& passHashOnce, std::string const& salt);
        void addUser(std::string const& name, std::string const& passHashOnce);

        void setup();
        void setupTables();
        void setupStatements();

    private:
        std::unique_ptr <soci::session> sql_;
        std::unordered_map <std::string, soci::statement> statements_;
        DatabaseConfig config_;
    };

} // namespace Database
} // namespace Server
} // namespace Carbonide

BOOST_FUSION_ADAPT_STRUCT
(
    Carbonide::Server::Database::DatabaseConfig,
    backend, dbName, user, password, host, port, charset
)


#endif // DATABASE_DATABASE_HPP_INCLUDED
