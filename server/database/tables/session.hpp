#pragma once

#include <table-cedsl/table_base.hpp>
#include <table-cedsl/field_types.hpp>

using namespace TableCesdl;

DECLARE_TABLE_3
(
    Sessions, (Carbonide)(Server)(Database)(Tables),
    (std::string, SessionID, TYPE(VARCHAR), SIZE(16), NOT_NULL, PRIMARY_KEY)
    (std::string, UserID, TYPE(VARCHAR), SIZE(16), NOT_NULL, FOREIGN_KEY((User)(UserID)))
    ,
    (
        CHARACTER_SET("utf8"),
        COLLATE("utf8_bin")
    )
)
