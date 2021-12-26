#include <cassert>
#include <cstdint>

#include <array>
#include <set>

#include <iostream>
#include <format>

#include <algorithm>
#include <numeric>
#include <ranges>




using namespace std::literals;
#include "include/thrower.h"
#include "include/stopwatch.h"

// need 3 groupings of equal weight.
// group with smallest number of packages needs minimum product

constexpr auto weights{std::array{1,3,5,11,13,17,19,23,29,31,37,41,43,47,53,59,67,71,73,79,83,89,97,101,103,107,109,113}};  // 28 items;  2^28 ~300 million.
constexpr auto total  {std::accumulate(weights.begin(),weights.end(),0)};
constexpr auto part1Target {total/3};
constexpr auto part2Target {total/4};

static_assert(total % 3 == 0);
static_assert(total % 4 == 0);


int sum(uint32_t subset)
{
    int sum{};

    for(int bit = 0; bit < weights.size(); bit++)
    {
        if( subset & (1 << bit))
        {
            sum+= weights[bit];
        }
    }

    return sum;
}

int64_t product(uint32_t subset)
{
    int64_t product{1};

    for(int bit = 0; bit < weights.size(); bit++)
    {
        if( subset & (1 << bit))
        {
            product *= weights[bit];

            if(product < 0)
            {
                return std::numeric_limits<int64_t>::max();
            }
        }
    }


    return product;
}



int main()
try
{
    std::set<uint32_t>        part1Candidates;    
    std::set<uint32_t>        part2Candidates;    

    Stopwatch   sw;

    for(uint32_t    subset=0; subset< (1u << weights.size()); subset++)
    {
        auto weight = sum(subset);

        if(weight ==  part1Target)
        {
            part1Candidates.insert(subset);            
        }

        if(weight ==  part2Target)
        {
            part2Candidates.insert(subset);            
        }

    }

    std::cout << std::format("Searched {} subsets in {}ms\n", 1<<weights.size(), sw.milliseconds());
    std::cout << std::format("Found {} part1 Candidates \n", part1Candidates.size());
    std::cout << std::format("Found {} part2 Candidates \n", part2Candidates.size());


    {
        // part 1 : assume subset with smallest QE overall is the right answer.   Ie. ignore whether the remaining packages can be split in 2 parts of the right weight.
        //          assumption works!
    
        int64_t  smallestQE{ std::numeric_limits<int64_t>::max()};

        for(auto candidate : part1Candidates)
        {
            smallestQE = std::min(smallestQE, product(candidate));
        }

        std::cout << std::format("Part 1 : smallestQE = {} \n",smallestQE);
    }

    {
        // part 2 : assume subset with smallest QE overall is the right answer.   Ie. ignore whether the remaining packages can be split in 3 parts of the right weight.
        //          assumption works again!  Is is guaranteed to work?  I doubt it.
    
        int64_t  smallestQE{ std::numeric_limits<int64_t>::max()};

        for(auto candidate : part2Candidates)
        {
            smallestQE = std::min(smallestQE, product(candidate));
        }

        std::cout << std::format("Part 2 : smallestQE = {} \n",smallestQE);
    }


    return 0;
}
catch(std::exception const &e)
{
    std::cout << e.what() << '\n';
}