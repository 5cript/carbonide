#ifndef MYNAMESPACE_TOKENS_H
#define MYNAMESPACE_TOKENS_H

#include <sqlpp11/table.h>
#include <sqlpp11/column_types.h>
#include <sqlpp11/char_sequence.h>

namespace Carbonide { namespace Server { namespace Database { namespace Tables {
{
  namespace Tokens_
  {
    struct Id
    {
      struct _alias_t
      {
        static constexpr const char _literal[] =  "id";
        using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
        template<typename T>
        struct _member_t
          {
            T id;
            T& operator()() { return id; }
            const T& operator()() const { return id; }
          };
      };
      using _traits = sqlpp::make_traits<sqlpp::integer, sqlpp::tag::can_be_null>;
    };
    struct AccessToken
    {
      struct _alias_t
      {
        static constexpr const char _literal[] =  "access_token";
        using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
        template<typename T>
        struct _member_t
          {
            T accessToken;
            T& operator()() { return accessToken; }
            const T& operator()() const { return accessToken; }
          };
      };
      using _traits = sqlpp::make_traits<sqlpp::text, sqlpp::tag::require_insert>;
    };
    struct TokenType
    {
      struct _alias_t
      {
        static constexpr const char _literal[] =  "token_type";
        using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
        template<typename T>
        struct _member_t
          {
            T tokenType;
            T& operator()() { return tokenType; }
            const T& operator()() const { return tokenType; }
          };
      };
      using _traits = sqlpp::make_traits<sqlpp::text, sqlpp::tag::require_insert>;
    };
    struct CreationDate
    {
      struct _alias_t
      {
        static constexpr const char _literal[] =  "creation_date";
        using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
        template<typename T>
        struct _member_t
          {
            T creationDate;
            T& operator()() { return creationDate; }
            const T& operator()() const { return creationDate; }
          };
      };
      using _traits = sqlpp::make_traits<sqlpp::varchar, sqlpp::tag::require_insert>;
    };
    struct ExpiresIn
    {
      struct _alias_t
      {
        static constexpr const char _literal[] =  "expires_in";
        using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
        template<typename T>
        struct _member_t
          {
            T expiresIn;
            T& operator()() { return expiresIn; }
            const T& operator()() const { return expiresIn; }
          };
      };
      using _traits = sqlpp::make_traits<sqlpp::integer, sqlpp::tag::can_be_null>;
    };
  }

  struct Tokens: sqlpp::table_t<Tokens,
               Tokens_::Id,
               Tokens_::AccessToken,
               Tokens_::TokenType,
               Tokens_::CreationDate,
               Tokens_::ExpiresIn>
  {
    struct _alias_t
    {
      static constexpr const char _literal[] =  "tokens";
      using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
      template<typename T>
      struct _member_t
      {
        T tokens;
        T& operator()() { return tokens; }
        const T& operator()() const { return tokens; }
      };
    };
  };
} // namespace Tables
} // namespace Database
} // namespace Server
} // namespace Carbonide
#endif
