#include <cassert>
#include <cstdint>

#include <tuple>
#include <string>
#include <vector>
#include <map>

#include <iostream>
#include <sstream>
#include <format>

#include <algorithm>
#include <numeric>
#include <ranges>

using namespace std::literals;
#include "include/thrower.h"

extern std::istringstream realData;

auto readData()
{
    std::multimap<std::string, std::string>  replacements;
    std::string                              molecule;

    std::string line;

    while(std::getline(realData,line)
          && !line.empty())
    {
        auto space=line.find(' ');

        auto source = line.substr(0,space);
        auto dest   = line.substr(space+4);

        replacements.emplace(source,dest);

    }

    std::getline(realData,molecule);

    assert(!molecule.empty());

    return std::make_pair(replacements,molecule);
}
int main()
try
{
    auto [replacements, molecule] = readData();


    return 0;
}
catch(std::exception const &e)
{
    std::cout << e.what() << '\n';
}