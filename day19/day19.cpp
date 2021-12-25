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

struct Recipe
{
    std::string original;
    std::string replacement;
};


auto readData()
{
    std::vector<Recipe>    replacements;
    std::string            molecule;

    std::string line;

    while(std::getline(realData,line)
          && !line.empty())
    {
        auto space=line.find(' ');

        auto original       = line.substr(0,space);
        auto replacement    = line.substr(space+4);

        replacements.emplace_back(original,replacement);

    }

    std::getline(realData,molecule);

    assert(!molecule.empty());

    return std::make_pair(replacements,molecule);
}


auto countPossibilities(std::vector<Recipe>     const &replacements,
                        std::string             const &molecule)
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



void part2_greedy(std::vector<Recipe>     const &replacements,
                  std::string             molecule)
{
    int count{};

    while(molecule != "e")
    {
        bool shortened{false};

        for(auto  &replacement : replacements)
        {
            size_t  pos;

            while((pos = molecule.find(replacement.replacement)) != molecule.npos)
            {
                molecule.replace(pos, replacement.replacement.size(), replacement.original);
                count++;
                shortened=true;
            }

        }

        if(!shortened)
        {
            std::cout << "Greedy didn't work";
            return;
        }
    }

    std::cout << "Part 2 : " << count << "\n";

}



int main()
try
{
    auto [replacements, molecule] = readData();

    auto part1=countPossibilities(replacements,molecule);

    std::cout  << std::format("Part 1 : {}\n", part1);


    auto length=[](auto const &lhs, auto const &rhs)
    {
        return rhs.replacement.size() < lhs.replacement.size();
    };

    std::ranges::sort(replacements, length);


    part2_greedy(replacements, molecule);

    return 0;
}
catch(std::exception const &e)
{
    std::cout << e.what() << '\n';
}