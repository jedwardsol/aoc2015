#include <cassert>
#include <cstdint>

#include <string>
#include <vector>

#include <iostream>
#include <sstream>
#include <format>

#include <algorithm>
#include <numeric>
#include <ranges>

using namespace std::literals;
#include "include/thrower.h"

extern std::string realData;

struct Present
{
    std::array<int,3> sides;


    auto area() const
    {
        return   3*sides[0] * sides[1]
               + 2*sides[1] * sides[2]
               + 2*sides[2] * sides[0];
    }

    auto perimeter() const
    {
        return  2*sides[0]
               +2*sides[1];
    }

    auto volume() const
    {
        return sides[0]*sides[1]*sides[2];
    }

};

std::istream &operator>>(std::istream &stream, Present &present)
{
    stream >> present.sides[0] >> present.sides[1] >> present.sides[2];
    std::ranges::sort(present.sides);
    return stream;
}


void part1(std::vector<Present>  const &presents)
{
    auto total = std::accumulate(presents.begin(), 
                                 presents.end(),
                                 0,
                                 [](auto total, auto &present)
                                 {
                                    return total + present.area();
                                 });


    std::cout << std::format("Part 1 : {} \n",total);
}


void part2(std::vector<Present>  const &presents)
{
    auto total = std::accumulate(presents.begin(), 
                                 presents.end(),
                                 0,
                                 [](auto total, auto &present)
                                 {
                                    return total + present.perimeter()+present.volume();
                                 });


    std::cout << std::format("Part 2 : {} \n",total);
}



int main()
try
{
    std::ranges::replace(realData,'x',' ');

    std::istringstream      stream{realData};
    std::vector<Present>    presents;

    Present present;

    while(stream >> present)
    {
        presents.push_back(present);
    }
    

    part1(presents);
    part2(presents);


    return 0;
}
catch(std::exception const &e)
{
    std::cout << e.what() << '\n';
}