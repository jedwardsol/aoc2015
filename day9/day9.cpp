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

/*
Faerun to Norrath = 129             Norrath to Tristram = 142
Faerun to Tristram = 58             Norrath to AlphaCentauri = 15
Faerun to AlphaCentauri = 13        Norrath to Arbre = 135
Faerun to Arbre = 24                Norrath to Snowdin = 75
Faerun to Snowdin = 60              Norrath to Tambi = 82
Faerun to Tambi = 71                Norrath to Straylight = 54
Faerun to Straylight = 67



Tristram to AlphaCentauri = 118     AlphaCentauri to Arbre = 116
Tristram to Arbre = 122             AlphaCentauri to Snowdin = 12
Tristram to Snowdin = 103           AlphaCentauri to Tambi = 18
Tristram to Tambi = 49              AlphaCentauri to Straylight = 91
Tristram to Straylight = 97


Arbre to Snowdin = 129              Snowdin to Tambi = 15
Arbre to Tambi = 53                 Snowdin to Straylight = 99
Arbre to Straylight = 40
                                    Tambi to Straylight = 70




*/

std::array<std::array<int,8>,8>  distances
{{
                  /*    Al  Ar   F   N  Sn  St  Ta  Tr
/* AlphaCentauri  */  {  0,116, 13, 15, 12, 91, 18,118},
/* Arbre          */  {116,  0, 24,135,129, 40, 53,122},
/* Faerun         */  { 13, 24,  0,129, 60, 67, 71, 58},
/* Norrath        */  { 15,135,129,  0, 75, 54, 82,142},
/* Snowdin        */  { 12,129, 60, 75,  0, 99, 15,103},
/* Straylight     */  { 91, 40, 67, 54, 99,  0, 70, 97},
/* Tambi          */  { 18, 53, 71, 82, 15, 70,  0, 49},
/* Tristram       */  {118,122, 58,142,103, 97, 49,  0},
}};



int main()
try
{
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            assert(distances[i][j]==distances[j][i]);
        }
    }

    int max{};
    int min{1'000'000};

    std::array  route{0,1,2,3,4,5,6,7};
    int         count{};

    Stopwatch   sw;

    do
    {
        count++;
        int distance{};

        for(int leg=0;leg<7;leg++)
        {
            distance+= distances[route[leg]][route[leg+1]];
        }

        max=std::max(max,distance);
        min=std::min(min,distance);

    } while(std::next_permutation(route.begin(),route.end()));

    std::cout << sw.milliseconds() << "ms\n";
 
    assert(count==8*7*6*5*4*3*2); 

    std::cout << "Min " << min << "\n";
    std::cout << "Max " << max << "\n";

    return 0;
}
catch(std::exception const &e)
{
    std::cout << e.what() << '\n';
}