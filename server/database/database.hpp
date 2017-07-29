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

#include <memory>
#include <string>
#include <boost/optional.hpp>

namespace Carbonide { namespace Server { namespace Database {

    struct DatabaseConfig : public JSON::Stringifiable <DatabaseConfig>
                          , public JSON::Parsable <DatabaseConfig>
    {
        std::string user;
        std::string password;
        boost::optional <std::string> database;
        boost::optional <std::string> host; // default = localhost
        boost::optional <uint32_t> port; // default = 3306
        boost::optional <std::string> charset;
    };

    class Database
    {
    public:
        Database();

        void connect(DatabaseConfig const& config);
        void disconnect();

        void addUser();

        void setupTables();

    private:
        std::unique_ptr <soci::session> sql_;
    };

} // namespace Database
} // namespace Server
} // namespace Carbonide

BOOST_FUSION_ADAPT_STRUCT
(
    Carbonide::Server::Database::DatabaseConfig,
    (std::string, user)
    (std::string, password)
    (boost::optional <std::string>, database)
    (boost::optional <std::string>, host)
    (boost::optional <uint32_t>, port)
    (boost::optional <std::string>, charset)
)


#endif // DATABASE_DATABASE_HPP_INCLUDED
