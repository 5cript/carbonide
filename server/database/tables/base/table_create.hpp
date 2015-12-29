#ifndef DATABASE_TABLES_BASE_TABLE_CREATE_HPP_INCLUDED
#define DATABASE_TABLES_BASE_TABLE_CREATE_HPP_INCLUDED

#include "table_base.hpp"

#include <vector>
#include <string>
#include <sstream>

namespace Carbonide { namespace Server { namespace Database { namespace Tables {

    template <typename TableT, typename StreamT>
    void createTableQuery(StreamT& stream, bool ignoreExisting = true)
    {
        using range = boost::mpl::range_c <int, 0, boost::fusion::result_of::size <TableT>::type::value>;

        stream << "CREATE TABLE ";
        if (ignoreExisting)
            stream << "IF NOT EXISTS ";

        stream << TableT::__name;

        stream << " (\n";

        boost::mpl::for_each <range> ([&](auto index) {
            using attribute = typename std::tuple_element <decltype(index)::value, typename TableT::attributes>::type;
            std::string name = boost::fusion::extension::struct_member_name<TableT, decltype(index)::value>::call();

            stream << "\t" << name << " " << attribute::type::getName();
            if (attribute::size != 0) {
                stream << "(" << attribute::size << ")";
            }

            if (attribute::notNull)
                stream << " NOT NULL";

            if (attribute::autoIncrement)
                stream << " AUTO_INCREMENT";

            if (attribute::primaryKey)
                stream << " PRIMARY KEY";

            if (decltype(index)::value < boost::fusion::result_of::size <TableT>::type::value - 1)
                stream << ",";

            stream << "\n";
        });

        stream << ")";

        if (TableT::tableAttributes::charsetSpecified)
            stream << " CHARACTER SET " << TableT::tableAttributes::charset;

        if (TableT::tableAttributes::collateSpecified)
            stream << " COLLATE " << TableT::tableAttributes::collate;
    }

    template <typename T>
    std::string createTableQuery(bool ignoreExisting = true)
    {
        std::stringstream sstr;
        createTableQuery <T>(sstr, ignoreExisting);
        return sstr.str();
    }

} // namespace Tables
} // namespace Database
} // namespace Server
} // namespace Carbonide

#endif // DATABASE_TABLES_BASE_TABLE_CREATE_HPP_INCLUDED
