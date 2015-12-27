#ifndef DATABASE_TABLES_BASE_TABLE_CREATE_HPP_INCLUDED
#define DATABASE_TABLES_BASE_TABLE_CREATE_HPP_INCLUDED

#include "table_base.hpp"

#include <vector>

namespace Carbonide { namespace Server { namespace Database { namespace Tables {

    template <typename TableT, typename StreamT>
    void createTableQuery(StreamT& stream, bool ignoreExisting = true) {
        using range = boost::mpl::range_c <int, 0, boost::fusion::result_of::size <TableT>::type::value>;

        stream << "CREATE TABLE ";
        if (ignoreExisting)
            stream << "IF NOT EXISTS ";
        stream << "(\n";

        boost::mpl::for_each <range> ([&](auto index) {
            using attribute = typename std::tuple_element <decltype(index)::value, typename TableT::attributes>::type;
            std::string name = boost::fusion::extension::struct_member_name<TableT, decltype(index)::value>::call();

            stream << "\t" << name << " " << attribute::type::getName();
            if (attribute::size != 0) {
                stream << "(" << attribute::size << ")";
            }

            if (attribute::notNull)
                stream << " NOT_NULL";

            if (attribute::autoIncrement)
                stream << " AUTO_INCREMENT";

            if (decltype(index)::value < boost::fusion::result_of::size <TableT>::type::value - 1)
                stream << ",";

            stream << "\n";
        });

        stream << ")";
    }

} // namespace Tables
} // namespace Database
} // namespace Server
} // namespace Carbonide

#include "undef_cleanup.hpp"

#endif // DATABASE_TABLES_BASE_TABLE_CREATE_HPP_INCLUDED
