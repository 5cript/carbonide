#ifndef DATABASE_TABLES_TABLE_BASE_HPP_INCLUDED
#define DATABASE_TABLES_TABLE_BASE_HPP_INCLUDED

#include <boost/fusion/adapted/struct/adapt_struct.hpp>
#include <boost/fusion/include/at.hpp>
#include <boost/fusion/include/for_each.hpp>
#include <boost/mpl/range_c.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/mpl/range_c.hpp>

#include <boost/optional.hpp>

#include <string>
#include <sstream>
#include <typeinfo>
#include <type_traits>
#include <tuple>

namespace Carbonide { namespace Server { namespace Database { namespace Tables {

    template <std::size_t S>
    using SizeTypeWrapper = std::integral_constant<std::size_t, S>;

    template <typename T,
              typename SpecialType,
              std::size_t Size,
              bool NotNull,
              bool AutoIncrement,
              bool PrimaryKey>
    struct FieldAttributes
    {
        using ctype = T;
        using type = SpecialType;

        // constexpr static produces linker error
        enum : std::size_t {
            size = Size
        };

        constexpr static const bool notNull = NotNull;
        constexpr static const bool autoIncrement = AutoIncrement;
        constexpr static const bool primaryKey = PrimaryKey;
    };

} // namespace Tables
} // namespace Database
} // namespace Server
} // namespace Carbonide

#include "preprocessor_includes.hpp"
#include "field_types.hpp"

#define OPT_WRAPPER boost::optional
#define OPT_NONE boost::none

////////////////////////// FIELD ATTRIBUTES /////////////////////////////
#define NIL_ARG (0)
#define NOT_NULL (1)
#define AUTO_INCREMENT (2)
#define SIZE_ID (3)
#define TYPE_ID (4)
#define PRIMARY_KEY (5)

#define SIZE(X) SIZE_ID(SizeTypeWrapper <X>)
#define TYPE(X) TYPE_ID(X)
/////////////////////////////////////////////////////////////////////////

////////////////////////// TABLE ATTRIBUTES /////////////////////////////
#define EPS_ATTRIBUTE (0)
#define CHARACTER_SET_ID (1)
#define COLLATE_ID (2)

#define CHARACTER_SET(X) CHARACTER_SET_ID(X)
#define COLLATE(X) COLLATE_ID(X)
/////////////////////////////////////////////////////////////////////////

#define MAX_ARGUMENTS 7

//##########################################################################################################

#define DEFL_NULL(...) 0
#define VOIDIFY(...)

#define VMAX_OP(d, state, x) BOOST_PP_MAX(state, x)

#define VMAX(...) \
    BOOST_PP_LIST_FOLD_LEFT(VMAX_OP, 0, BOOST_PP_TUPLE_TO_LIST((__VA_ARGS__)))

//##########################################################################################################

#define SET_TUPLE_SIZE_PRED(r, pair) \
    BOOST_PP_NOT_EQUAL ( \
        BOOST_PP_TUPLE_ELEM(3, 1, pair), \
        BOOST_PP_TUPLE_SIZE(BOOST_PP_TUPLE_ELEM(3, 0, pair)) \
    )

#define SET_TUPLE_SIZE_OP(r, state) \
    (BOOST_PP_TUPLE_PUSH_BACK(BOOST_PP_TUPLE_ELEM(3, 0, state), NIL_ARG), BOOST_PP_TUPLE_ELEM(3, 1, state))

#define SET_TUPLE_SIZE_M(r, state) (BOOST_PP_TUPLE_ELEM(3, 0, state))

#define SET_TUPLE_SIZE_F(tuple, size) \
    BOOST_PP_FOR((tuple, BOOST_PP_INC(size)), SET_TUPLE_SIZE_PRED, SET_TUPLE_SIZE_OP, SET_TUPLE_SIZE_M)

#define SET_TUPLE_SIZE(tuple, size) \
    BOOST_PP_TUPLE_ELEM( \
        BOOST_PP_INC(BOOST_PP_SUB(size, BOOST_PP_TUPLE_SIZE(tuple))), \
        BOOST_PP_SUB(size, BOOST_PP_TUPLE_SIZE(tuple)), \
        BOOST_PP_SEQ_TO_TUPLE(SET_TUPLE_SIZE_F(tuple, size)) \
    )

//##########################################################################################################

#define SEQUENCE_FACTORY_0(...) \
     ((__VA_ARGS__)) SEQUENCE_FACTORY_1
#define SEQUENCE_FACTORY_1(...) \
     ((__VA_ARGS__)) SEQUENCE_FACTORY_0
#define SEQUENCE_FACTORY_0_END
#define SEQUENCE_FACTORY_1_END

//##########################################################################################################

#define IS_IN_FIELD_TUPLE_FOLD_OP(d, state, x) \
    (BOOST_PP_SEQ_HEAD(state)) \
    (BOOST_PP_MAX(BOOST_PP_EQUAL(BOOST_PP_SEQ_HEAD(state), BOOST_PP_SEQ_HEAD(x)), BOOST_PP_SEQ_ELEM(1, state)))

#define IS_IN_FIELD_TUPLE_IMPL(tuple, what) \
    BOOST_PP_SEQ_ELEM(1, \
        BOOST_PP_SEQ_FOLD_LEFT( \
            IS_IN_FIELD_TUPLE_FOLD_OP, \
            what(0), \
            BOOST_PP_TUPLE_TO_SEQ(BOOST_PP_TUPLE_POP_FRONT(BOOST_PP_TUPLE_POP_FRONT(tuple))) \
        ) \
    )

#define IS_IN_FIELD_TUPLE(tuple, what) \
    BOOST_PP_IF(BOOST_PP_LESS(BOOST_PP_TUPLE_SIZE(tuple), 3), DEFL_NULL, IS_IN_FIELD_TUPLE_IMPL)(tuple, what)


//##########################################################################################################

#define UNSPECIFIED_TYPE(tuple) DetermineFieldType <BOOST_PP_SEQ_HEAD(BOOST_PP_TUPLE_TO_SEQ(tuple))>::type

#define EXTRACT_TYPE_PRED(s, data, elem) \
    BOOST_PP_EQUAL(BOOST_PP_SEQ_HEAD(TYPE_ID), BOOST_PP_SEQ_HEAD(elem))

#define EXTRACT_TYPE_IMPL(tuple) \
    BOOST_PP_SEQ_ELEM(1, BOOST_PP_SEQ_HEAD(BOOST_PP_SEQ_FILTER(EXTRACT_TYPE_PRED, ~, BOOST_PP_TUPLE_TO_SEQ( \
        BOOST_PP_TUPLE_POP_FRONT(BOOST_PP_TUPLE_POP_FRONT(tuple)) \
    ))))

#define EXTRACT_TYPE(tuple) \
    BOOST_PP_IF(BOOST_PP_AND( \
        IS_IN_FIELD_TUPLE(tuple, TYPE_ID), \
        BOOST_PP_GREATER(BOOST_PP_TUPLE_SIZE(tuple), 2) \
    ), EXTRACT_TYPE_IMPL, UNSPECIFIED_TYPE)(tuple)

//##########################################################################################################

#define UNSPECIFIED_SIZE(...) SizeTypeWrapper <0>

#define EXTRACT_TYPE_SIZE_PRED(s, data, elem) \
    BOOST_PP_EQUAL(BOOST_PP_SEQ_HEAD(SIZE_ID), BOOST_PP_SEQ_HEAD(elem))

#define EXTRACT_TYPE_SIZE_IMPL(tuple) \
    BOOST_PP_SEQ_ELEM(1, BOOST_PP_SEQ_HEAD(BOOST_PP_SEQ_FILTER(EXTRACT_TYPE_SIZE_PRED, ~, BOOST_PP_TUPLE_TO_SEQ( \
        BOOST_PP_TUPLE_POP_FRONT(BOOST_PP_TUPLE_POP_FRONT(tuple)) \
    ))))

#define EXTRACT_TYPE_SIZE(tuple) \
    BOOST_PP_IF(BOOST_PP_AND( \
        IS_IN_FIELD_TUPLE(tuple, SIZE_ID), \
        BOOST_PP_GREATER(BOOST_PP_TUPLE_SIZE(tuple), 2) \
    ), EXTRACT_TYPE_SIZE_IMPL, UNSPECIFIED_SIZE)(tuple)

//##########################################################################################################

#define TUPLE_NOT_EMPTY(tuple) \
    BOOST_PP_DEC(BOOST_PP_SEQ_SIZE(EPS_ATTRIBUTE BOOST_PP_TUPLE_ELEM(1, 0, tuple)))

#define CONTAINS_ATTRIBUTE_PRED(r, data, elem) \
    BOOST_PP_EQUAL(BOOST_PP_SEQ_HEAD(data), BOOST_PP_SEQ_HEAD(elem))

#define CONTAINS_ATTRIBUTE_IMPL(tuple, what) \
    BOOST_PP_SEQ_HEAD(BOOST_PP_SEQ_HEAD( \
        BOOST_PP_SEQ_FILTER( \
            CONTAINS_ATTRIBUTE_PRED, \
            what, \
            BOOST_PP_TUPLE_TO_SEQ(tuple) \
        )(EPS_ATTRIBUTE) \
    ))

#define CONTAINS_ATTRIBUTE(tuple, what) \
    BOOST_PP_IF(TUPLE_NOT_EMPTY(tuple), CONTAINS_ATTRIBUTE_IMPL, DEFL_NULL)(tuple, what)

#define EXTRACT_TABLE_ATTRIBUTE_PRED(s, data, elem) \
    BOOST_PP_EQUAL(BOOST_PP_SEQ_HEAD(data), BOOST_PP_SEQ_HEAD(elem))

#define EXTRACT_TABLE_ATTRIBUTE_IMPL(tuple, what) \
    BOOST_PP_SEQ_ELEM(1, \
        BOOST_PP_SEQ_HEAD( \
            BOOST_PP_SEQ_FILTER( \
                EXTRACT_TABLE_ATTRIBUTE_PRED, \
                what, \
                BOOST_PP_TUPLE_TO_SEQ( \
                    tuple \
                ) \
            ) \
        ) \
    )

#define EMPTY_TABLE_ATTRIBUTE(...) ""

#define EXTRACT_TABLE_ATTRIBUTE(tuple, what) \
    BOOST_PP_IF(CONTAINS_ATTRIBUTE(tuple, what), EXTRACT_TABLE_ATTRIBUTE_IMPL, EMPTY_TABLE_ATTRIBUTE)(tuple, what)

//##########################################################################################################

#define TABLE_FIELD(r, data, field_tuple) \
    data<BOOST_PP_TUPLE_ELEM(MAX_ARGUMENTS, 0, SET_TUPLE_SIZE(field_tuple, MAX_ARGUMENTS))> BOOST_PP_TUPLE_ELEM(MAX_ARGUMENTS, 1, SET_TUPLE_SIZE(field_tuple, MAX_ARGUMENTS));

#define TABLE_FIELD_INITIALIZER(r, data, i, field_tuple) \
    BOOST_PP_IF(IS_IN_FIELD_TUPLE(field_tuple, AUTO_INCREMENT),, \
        (BOOST_PP_TUPLE_ELEM(MAX_ARGUMENTS, 1, SET_TUPLE_SIZE(field_tuple, MAX_ARGUMENTS)){BOOST_PP_TUPLE_ELEM(MAX_ARGUMENTS, 1, SET_TUPLE_SIZE(field_tuple, MAX_ARGUMENTS))}) \
    )

#define TABLE_CONSTRUCTOR_PARAMETERS(r, data, i, field_tuple) \
    BOOST_PP_IF( \
        IS_IN_FIELD_TUPLE(field_tuple, AUTO_INCREMENT),, \
        (BOOST_PP_TUPLE_ELEM(2, 0, data)<BOOST_PP_TUPLE_ELEM(MAX_ARGUMENTS, 0, SET_TUPLE_SIZE(field_tuple, MAX_ARGUMENTS))> \
        BOOST_PP_TUPLE_ELEM(MAX_ARGUMENTS, 1, SET_TUPLE_SIZE(field_tuple, MAX_ARGUMENTS)) = \
            BOOST_PP_TUPLE_ELEM(2, 1, data)) \
    )

#define BOOLEAN_ATTRIBUTE(field_tuple, attr) \
    BOOST_PP_IF(IS_IN_FIELD_TUPLE(field_tuple, attr), true, false)

#define TABLE_ATTRIBUTES(r, data, i, field_tuple) \
    BOOST_PP_COMMA_IF(i) FieldAttributes <\
        BOOST_PP_TUPLE_ELEM(MAX_ARGUMENTS, 0, SET_TUPLE_SIZE(field_tuple, MAX_ARGUMENTS)), \
        EXTRACT_TYPE(field_tuple), \
        EXTRACT_TYPE_SIZE(field_tuple)::value, \
        BOOLEAN_ATTRIBUTE(field_tuple, NOT_NULL), \
        BOOLEAN_ATTRIBUTE(field_tuple, AUTO_INCREMENT), \
        BOOLEAN_ATTRIBUTE(field_tuple, PRIMARY_KEY) \
    >

#define TABLE_ADAPT_ENTRY(r, data, field_tuple) \
    (BOOST_PP_TUPLE_ELEM(MAX_ARGUMENTS, 1, SET_TUPLE_SIZE(field_tuple, MAX_ARGUMENTS)))

#define NAMESPACE_SEQ_EACH(r, data, elem) \
    namespace elem {

#define NAMESPACE_COLON_SEQ_EACH(r, data, i, elem) \
    BOOST_PP_IF(i, ::, BOOST_PP_EMPTY()) elem

#define NAMESPACE_SEQ(nspace) \
    BOOST_PP_SEQ_FOR_EACH(NAMESPACE_SEQ_EACH, ~, nspace)

#define NAMESPACE_COLON_SEQ(nspace) \
    BOOST_PP_SEQ_FOR_EACH_I(NAMESPACE_COLON_SEQ_EACH, ::, nspace)

#define CLOSING_CURLY(...) }

#define DECLARE_TABLE_IMPL(struct_name, fields, nspace, table_attributes) \
    NAMESPACE_SEQ(nspace) \
        struct struct_name { \
            BOOST_PP_SEQ_FOR_EACH(TABLE_FIELD, OPT_WRAPPER, fields) \
            \
            using attributes = std::tuple < \
                BOOST_PP_SEQ_FOR_EACH_I(TABLE_ATTRIBUTES, ~, fields) \
            >; \
            \
            constexpr static const char* __name = #struct_name;\
            \
            explicit struct_name( \
                BOOST_PP_SEQ_ENUM( \
                    BOOST_PP_SEQ_FOR_EACH_I(TABLE_CONSTRUCTOR_PARAMETERS, (OPT_WRAPPER, OPT_NONE), fields) \
                ) \
            ) \
            : \
            BOOST_PP_SEQ_ENUM( \
                BOOST_PP_SEQ_FOR_EACH_I(TABLE_FIELD_INITIALIZER, OPT_NONE, fields) \
            ) \
            {} \
            \
            typedef struct __TableAttributes { \
                constexpr static const char* charset = EXTRACT_TABLE_ATTRIBUTE(table_attributes, CHARACTER_SET_ID); \
                constexpr static const char* collate = EXTRACT_TABLE_ATTRIBUTE(table_attributes, COLLATE_ID); \
                \
                constexpr static const bool charsetSpecified = charset[0] != '\0'; \
                constexpr static const bool collateSpecified = collate[0] != '\0'; \
            } tableAttributes; \
            \
        }; \
    BOOST_PP_SEQ_FOR_EACH(CLOSING_CURLY, ~, nspace) \
    \
    BOOST_FUSION_ADAPT_STRUCT \
    ( \
        NAMESPACE_COLON_SEQ(nspace) :: struct_name, \
        BOOST_PP_SEQ_ENUM( \
            BOOST_PP_SEQ_FOR_EACH(TABLE_ADAPT_ENTRY, nspace, fields) \
        ) \
    )

#define DECLARE_TABLE(struct_name, fields) \
     DECLARE_TABLE_IMPL(struct_name, \
                        BOOST_PP_CAT(SEQUENCE_FACTORY_0 fields,_END),,) \

#define DECLARE_TABLE_2(struct_name, nspace, fields) \
     DECLARE_TABLE_IMPL(struct_name, \
                        BOOST_PP_CAT(SEQUENCE_FACTORY_0 fields,_END), \
                        nspace,)

#define DECLARE_TABLE_3(struct_name, nspace, fields, table_attributes) \
     DECLARE_TABLE_IMPL(struct_name, \
                        BOOST_PP_CAT(SEQUENCE_FACTORY_0 fields,_END), \
                        nspace, \
                        table_attributes)
//##########################################################################################################

#endif // DATABASE_TABLES_TABLE_BASE_HPP_INCLUDED
