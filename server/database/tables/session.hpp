#pragma once

#include <table-cedsl/table_base.hpp>
#include <table-cedsl/field_types.hpp>

using namespace TableCesdl;

DECLARE_TABLE_3
(
    Sessions, (Carbonide)(Server)(Database)(Tables),
    (std::vector <char>, SessionID, TYPE(BLOB), SIZE(16), NOT_NULL, PRIMARY_KEY)
    (std::vector <char>, UserID, TYPE(BLOB), SIZE(16), NOT_NULL, REFERENCES(Users, UserID))
    ,
    (
        CHARACTER_SET("utf8"),
        COLLATE("utf8_bin")
    )
)

#include <table-cedsl/undef_cleanup.hpp>
