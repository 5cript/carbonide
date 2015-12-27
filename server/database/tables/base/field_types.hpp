#ifndef DATABASE_TABLES_BASE_FIELD_TYPES_HPP_INCLUDED
#define DATABASE_TABLES_BASE_FIELD_TYPES_HPP_INCLUDED

#include <ctime>

namespace Carbonide { namespace Server { namespace Database { namespace Tables {

#   define DECLARE_TYPE(NAME) \
    struct NAME { \
        static constexpr const char* getName() { return #NAME; } \
    }

    // special
    DECLARE_TYPE(JSON);

    // strings
    DECLARE_TYPE(CHAR);
    DECLARE_TYPE(VARCHAR);
    DECLARE_TYPE(BINARY);
    DECLARE_TYPE(VARBINARY);
    DECLARE_TYPE(BLOB);
    DECLARE_TYPE(TEXT);
    DECLARE_TYPE(ENUM);
    DECLARE_TYPE(SET);

    // numeric
    DECLARE_TYPE(INTEGER);
    DECLARE_TYPE(SMALLINT);
    DECLARE_TYPE(FLOAT);
    DECLARE_TYPE(DOUBLE);

    // time
    DECLARE_TYPE(DATE);
    DECLARE_TYPE(TIME);
    DECLARE_TYPE(DATETIME);
    DECLARE_TYPE(TIMESTAMP);
    DECLARE_TYPE(YEAR);

    template <typename>
    struct DetermineFieldType {};

#   define TRANSLATE_TYPE(from, to) \
    template <> \
    struct DetermineFieldType <from> { \
        using type = to; \
    }

    TRANSLATE_TYPE(int, INTEGER);
    // TRANSLATE_TYPE(short, SMALLINT);
    // TRANSLATE_TYPE(float, FLOAT);
    TRANSLATE_TYPE(double, DOUBLE);
    TRANSLATE_TYPE(std::string, TEXT);
    TRANSLATE_TYPE(std::tm, TIMESTAMP);

    #undef DECLARE_TYPE
    #undef TRANSLATE_TYPE

} // namespace Tables
} // namespace Database
} // namespace Server
} // namespace Carbonide

#endif // DATABASE_TABLES_BASE_FIELD_TYPES_HPP_INCLUDED
