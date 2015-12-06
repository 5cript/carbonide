#ifndef DATABASE_DATABASE_HPP_INCLUDED
#define DATABASE_DATABASE_HPP_INCLUDED

#include "tables.hpp"

#include <memory>

namespace Carbonide { namespace Server { namespace Database {

    class Database
    {
        virtual ~Database() = default;
    };

} // namespace Database
} // namespace Server
} // namespace Carbonide


#endif // DATABASE_DATABASE_HPP_INCLUDED
