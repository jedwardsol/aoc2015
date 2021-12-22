#include <cassert>
#include <cstdint>

#include <string>
#include <map>

#include <iostream>
#include <sstream>
#include <format>

#include <algorithm>
#include <numeric>
#include <ranges>

using namespace std::literals;
#include "include/thrower.h"

extern std::string realData;


struct Location
{
    int row;
    int column;

    auto operator<=>(Location const&rhs) const noexcept = default;

};



void part1()
{
    std::map<Location,int>      houses;
    Location                    current{};

    houses[current]=1;

    for(auto c : realData)
    {
        switch(c)
        {
        case '^':   current.row--; break;            
        case 'v':   current.row++; break;            
        case '<':   current.column--; break;            
        case '>':   current.column++; break;            
        default:    throw_runtime_error("bad direction");
        }

        houses[current]++;
    }

    std::cout << std::format("Part 1 : {} \n",houses.size());
}


void part2()
{
    std::map<Location,int>      houses;
    Location                    postman[2]{};
    int                         current=0;

    houses[postman[0]]++;
    houses[postman[1]]++;

    for(auto c : realData)
    {
        switch(c)
        {
        case '^':   postman[current].row--; break;            
        case 'v':   postman[current].row++; break;            
        case '<':   postman[current].column--; break;            
        case '>':   postman[current].column++; break;            
        default:    throw_runtime_error("bad direction");
        }

        houses[postman[current]]++;

        current=!current;
    }

    std::cout << std::format("Part 2 : {} \n",houses.size());
}





int main()
try
{
    part1();
    part2();


    return 0;
}
catch(std::exception const &e)
{
    std::cout << e.what() << '\n';
}