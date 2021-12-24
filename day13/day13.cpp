#include <cassert>
#include <cstdint>

#include <array>
#include <map>

#include <iostream>
#include <sstream>
#include <format>

#include <algorithm>
#include <numeric>
#include <ranges>

using namespace std::literals;
#include "include/thrower.h"
#include "include/stopwatch.h"

extern std::istringstream data;

// same as day 9,  but 9! permutations instead of 8!.  Brute force still takes just 3ms 

// gets bad at 12!

/*

Part 1 : 733 in 0ms
Part 2 : 725 in 3ms
11 : 725 in     1136 ms
12 : 725 in    15277 ms          15s
13 : 725 in   214780 ms           3.5 minutes

*/

std::map<std::string,int> index
{
    {"Alice"s,  0},
    {"Bob"s,    1},
    {"Carol"s,  2},
    {"David"s,  3},
    {"Eric"s,   4},
    {"Frank"s,  5},
    {"George"s, 6},
    {"Mallory"s,7},
};


std::array<std::array<int,20>,20>  happiness
{{
                  /*     A   B   C   D   E   F   G   M  Me
/* Alice          */  {  0,  0,  0,  0,  0,  0,  0,  0,  0},
/* Bob            */  {  0,  0,  0,  0,  0,  0,  0,  0,  0},
/* Carol          */  {  0,  0,  0,  0,  0,  0,  0,  0,  0},
/* David          */  {  0,  0,  0,  0,  0,  0,  0,  0,  0},
/* Eric           */  {  0,  0,  0,  0,  0,  0,  0,  0,  0},
/* Frank          */  {  0,  0,  0,  0,  0,  0,  0,  0,  0},
/* George         */  {  0,  0,  0,  0,  0,  0,  0,  0,  0},
/* Mallory        */  {  0,  0,  0,  0,  0,  0,  0,  0,  0},
/* Me             */  {  0,  0,  0,  0,  0,  0,  0,  0,  0},
}};



void fillArray()
{
    std::string line;

    std::string positive{"would gain "};
    std::string negative{"would lose "};
    std::string ignore  {"happiness units by sitting next to"};

    while(std::getline(data,line))
    {
        if(line.empty())
        {
            continue;
        }

        if(line.back()=='.')
        {
            line.pop_back();
        }

        auto pos = line.find(positive);
        if(pos!=line.npos)
        {
            line.replace(pos, positive.size(), "+");
        }

        pos = line.find(negative);
        if(pos!=line.npos)
        {
            line.replace(pos, negative.size(), "-");
        }

        pos = line.find(ignore);
        if(pos!=line.npos)
        {
            line.replace(pos, ignore.size(), "");
        }

        std::string sitter;
        int         joy;
        std::string neighbour;

        std::istringstream stream{line};

        stream >> sitter >> joy >> neighbour;

        happiness[ index[sitter] ] [index[neighbour] ] = joy;
    }


    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            if(i==j)  assert(happiness[i][j] == 0);
            else      assert(happiness[i][j] != 0);
        }
    }
}

template <size_t N>
auto solve()
{
    int max{};

    std::array<int,N>  arrangement;

    std::iota(arrangement.begin(), arrangement.end(),0);

    Stopwatch   sw;

    do
    {
        int totalHappiness{};

        for(int seat=0;seat<N;seat++)
        {
            int before = arrangement [ (seat -1 + N) % N];
            int sitter = arrangement [ seat ];
            int after  = arrangement [ (seat + 1) % N];

            totalHappiness+= happiness[sitter][before];
            totalHappiness+= happiness[sitter][after];
        }

        max=std::max(max,totalHappiness);

    } while(std::next_permutation(arrangement.begin(),arrangement.end()));

    return std::make_pair(max,sw.milliseconds());
}


template<size_t N>
void go()
{
    auto[result, time] = solve<N>();
    std::cout << std::format("{} : {} in {:8} ms\n", N, result, time);
}

int main()
try
{
    fillArray();

    auto[part1, time1] = solve<8>();
    auto[part2, time2] = solve<9>();

    std::cout << std::format("Part 1 : {} in {}ms\n", part1, time1);
    std::cout << std::format("Part 2 : {} in {}ms\n", part2, time2);

    go<11>();
    go<12>();
    go<13>();
    go<14>();
    go<15>();


    return 0;
}
catch(std::exception const &e)
{
    std::cout << e.what() << '\n';
}