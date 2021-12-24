#include <cassert>
#include <cstdint>

#include <array>
#include <vector>

#include <iostream>
#include <sstream>
#include <format>

using namespace std::literals;
#include "include/thrower.h"


struct Deer
{
    std::string name;
    int         speed;
    int         flyTime;
    int         restTime;
};

std::vector<Deer>       testDeer
{
    {"Comet"s,   14, 10, 127 },
    {"Dancer"s,  16, 11, 162  },
};

std::vector<Deer>       deer
{
    {"Vixen"s,    8,  8, 53 },
    {"Blitzen"s, 13,  4, 49 },
    {"Rudolph"s, 20,  7, 132},
    {"Cupid"s,   12,  4, 43 },
    {"Donner"s,   9,  5, 38 },
    {"Dasher"s,  10,  4, 37 },
    {"Comet"s,    3, 37, 76 },
    {"Prancer"s,  9, 12, 97 },
    {"Dancer"s,  37,  1, 36 },
};


int distance(Deer const &deer, int seconds)
{
    int distance{};

    auto const period = deer.flyTime + deer.restTime;

    distance = seconds / period * deer.flyTime * deer.speed;


    auto const remainder = std::min(seconds % period, deer.flyTime);

    distance += remainder * deer.speed;

    return distance;
}

void part1()
{
    int maxDistance{};

    for(auto const &deer : ::deer)
    {
        maxDistance = std::max(maxDistance, distance(deer,2503));    
    }

    std::cout << std::format("Part 1 : {}km\n",maxDistance);
}


void part2()
{
    std::array<int,9>   scores{};


    for(int s=1;s<=2503;s++)
    {
        int maxDistance{};
        int leader{};

        for(auto deer : ::deer)
        {
            maxDistance = std::max(maxDistance,distance(deer,s));
        }
        
        for(int i=0;i<9;i++)
        {
            if(distance(deer[i],s) == maxDistance)
            {
                scores[i]++;
            }
        }
    }

    std::ranges::sort(scores);

    std::cout << std::format("Part 2 : {}\n",scores[8]);
}



void test()
{
    assert(distance(testDeer[0],1000) == 1120);
    assert(distance(testDeer[1],1000) == 1056);
}


int main()
try
{
    test();
    part1();
    part2();


    return 0;
}
catch(std::exception const &e)
{
    std::cout << e.what() << '\n';
}