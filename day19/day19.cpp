#include <cassert>
#include <cstdint>

#include <tuple>
#include <string>
#include <vector>
#include <map>
#include <set>

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

        auto original       = line.substr(0,space);
        auto replacement    = line.substr(space+4);

        replacements.emplace(original,replacement);

    }

    std::getline(realData,molecule);

    assert(!molecule.empty());

    return std::make_pair(replacements,molecule);
}


auto countPossibilities(std::multimap<std::string, std::string>  const &replacements,
                        std::string  const                             &molecule)
{
    std::set<std::string>   distinctMolecules;

    for(auto &[original, replacement] : replacements)
    {
        size_t walk{};

        while((walk = molecule.find(original,walk+1)) != molecule.npos)
        {
            auto newMolecule{molecule};

            newMolecule.replace(walk, original.size(), replacement);
            
            distinctMolecules.insert(newMolecule);
        }
    }

    return distinctMolecules.size();
}


int main()
try
{
    auto [replacements, molecule] = readData();

    auto part1=countPossibilities(replacements,molecule);

    std::cout  << std::format("Part 1 : {} ", part1);

    return 0;
}
catch(std::exception const &e)
{
    std::cout << e.what() << '\n';
}