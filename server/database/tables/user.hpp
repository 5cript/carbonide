#pragma once

#include <table-cedsl/table_base.hpp>
#include <table-cedsl/field_types.hpp>

using namespace TableCesdl;

DECLARE_TABLE_3
(
    Users, (Carbonide)(Server)(Database)(Tables),
    (std::vector <char>, UserID, TYPE(BLOB), SIZE(16), NOT_NULL, PRIMARY_KEY)
    (std::string, Name, TYPE(VARCHAR), SIZE(255), NOT_NULL)
    (std::string, PassHash, TYPE(VARCHAR), SIZE(255), NOT_NULL)
    (std::string, Salt, TYPE(VARCHAR), SIZE(255), NOT_NULL)
    ,
    (
        CHARACTER_SET("utf8"),
        COLLATE("utf8_bin")
    )
)

#include <table-cedsl/undef_cleanup.hpp>
