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
constexpr uint32_t   targetVolume=150;

void go()
{
    std::array<int,21>  sizeCount{};            //   sizeCount[3]  is the number of combinations of 3 containers with a volume of 150

   
    // 20 : therefore ~1,000,000 combinations .  43ms

    Stopwatch sw;

    for(uint32_t combination = 1; combination < 1u<<containers.size(); combination++)
    {
        uint32_t volume{};

        for(int bit=0;bit < containers.size(); bit++)
        {
            if(combination & 1<<bit)
            {
                volume+=containers[bit];
            }
        }

        if(volume==targetVolume)
        {
            sizeCount[__popcnt(combination)]++;
        }
    }

    std::cout << std::format("part 1 : {} in {}ms\n", std::accumulate(sizeCount.begin(), sizeCount.end(),0) , sw.milliseconds());

    for(int i=0;i<sizeCount.size();i++)
    {
        std::cout << std::format("{:3} ways to use {:2} containers\n",sizeCount[i],i);
    }

}

int main()
try
{
    go();


    return 0;
}
catch(std::exception const &e)
{
    std::cout << e.what() << '\n';
}