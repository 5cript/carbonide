#include <iostream>

#include "../lib/SimpleREST/restful.hpp"
#include "database.hpp"

#include <fstream>

int main()
{
    using namespace Rest;

    InterfaceProvider api(8081);

    api.start();

    std::cin.get();

    return 0;
}
