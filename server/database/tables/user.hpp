#ifndef DATABASE_TABLES_USER_HPP_INCLUDED
#define DATABASE_TABLES_USER_HPP_INCLUDED

#include "base/table_base.hpp"

DECLARE_TABLE
(
    User, (Carbonide)(Server)(Database)(Tables),
    (int, id, NOT_NULL, AUTO_INCREMENT)
    (std::string, name, TYPE(VARCHAR), SIZE(128))
)

#include "base/undef_cleanup.hpp"

#endif // DATABASE_TABLES_USER_HPP_INCLUDED
