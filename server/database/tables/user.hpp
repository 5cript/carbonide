#pragma once

#include <table-cedsl/table_base.hpp>
#include <table-cedsl/field_types.hpp>

using namespace TableCesdl;

DECLARE_TABLE_3
(
    Users, (Carbonide)(Server)(Database)(Tables),
    (std::string, UserID, TYPE(VARCHAR), SIZE(16), NOT_NULL, PRIMARY_KEY)
    (std::string, Email, TYPE(VARCHAR), SIZE(255), NOT_NULL)
    (std::string, Name, TYPE(VARCHAR), SIZE(255), NOT_NULL)
    (std::string, PassHash, TYPE(VARCHAR), SIZE(255), NOT_NULL)
    (std::string, Salt, TYPE(VARCHAR), SIZE(32), NOT_NULL)
    (std::vector <unsigned char>, Permissions, TYPE(BLOB), SIZE(16), NOT_NULL)
    ,
    (
        CHARACTER_SET("utf8"),
        COLLATE("utf8_bin")
    )
)
