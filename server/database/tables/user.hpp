#ifndef DATABASE_TABLES_USER_HPP_INCLUDED
#define DATABASE_TABLES_USER_HPP_INCLUDED

#include "base/table_base.hpp"

DECLARE_TABLE_3
(
    User, (Carbonide)(Server)(Database)(Tables),
    (int, UserID, NOT_NULL, PRIMARY_KEY, AUTO_INCREMENT)
    (std::string, Name, TYPE(VARCHAR), SIZE(255), NOT_NULL)
    (std::string, PassHash, TYPE(VARCHAR), SIZE(255), NOT_NULL)
    (std::string, Salt, TYPE(VARCHAR), SIZE(255), NOT_NULL)
    ,
    (
        CHARACTER_SET("utf8"),
        COLLATE("utf8_bin")
    )
)
#endif // DATABASE_TABLES_USER_HPP_INCLUDED
