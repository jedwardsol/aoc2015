#include <cassert>
#include <cstdint>

#include <array>
#include <vector>
#include <deque>

#include <iostream>
#include <sstream>
#include <format>

#include <algorithm>
#include <numeric>
#include <ranges>

using namespace std::literals;
#include "include/thrower.h"
#include "include/stopwatch.h"

constexpr std::array containers{43,3,4,10,21,44,4,6,47,41,34,17,17,44,36,31,46,9,27,38};
constexpr uint32_t   target=150;

void part1()
{
    int matchingCombinations{};
   
    // 20 : therefore ~1,000,000 combinations .  43ms

    Stopwatch sw;

    for(uint32_t combination = 1; combination < 1<<containers.size(); combination++)
    {
        uint32_t total{};

        for(int bit=0;bit < containers.size(); bit++)
        {
            if(combination & 1<<bit)
            {
                total+=containers[bit];
            }
        }

        if(total==target)
        {
            matchingCombinations++;
        }
    }

    std::cout << std::format("part 1 : {} in {}ms\n",matchingCombinations , sw.milliseconds());
}

int main()
try
{
    part1();


    return 0;
}
catch(std::exception const &e)
{
    std::cout << e.what() << '\n';
}