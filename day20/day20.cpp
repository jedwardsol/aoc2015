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

extern std::istringstream data;

/*
House 1 got 10 presents.
House 2 got 30 presents.
House 3 got 40 presents.
House 4 got 70 presents.
House 5 got 60 presents.
House 6 got 120 presents.
House 7 got 80 presents.
House 8 got 150 presents.
House 9 got 130 presents.

*/


/* brute force - I bet there's an algebraic way! */

int numPresents_part1(int house)
{
    int count{};

    for(int elf=1;elf<=house;elf++)
    {
        if(house%elf==0)
        {
            count+=elf;
        }
    }

//  std::cout << std::format("{:4} : {:>9}\n",house,count*10);

    return count*10;
}


int numPresents_part2(int house)
{
    int count{};

    for(int elf=1;elf<=house;elf++)
    {
        if(   house%elf==0
           && house/elf < 50)
        {
            count+=elf;
        }
    }


    return count*11;
}



int main()
try
{
/*
   assert(numPresents(1)==10 );
   assert(numPresents(2)==30 );
   assert(numPresents(3)==40 );
   assert(numPresents(4)==70 );
   assert(numPresents(5)==60 );
   assert(numPresents(6)==120);
   assert(numPresents(7)==80 );
   assert(numPresents(8)==150);
   assert(numPresents(9)==130);

    int house1{1};

    while(numPresents_part1(house1) < 36'000'000)
    {
        house1++;
    }

    std::cout << std::format("Part 1 : {}\n",house1);
*/



    int house2{1};

    while(numPresents_part2(house2) < 36'000'000)
    {
        house2++;
    }

    std::cout << std::format("Part 2 : {}\n",house2);



    return 0;
}
catch(std::exception const &e)
{
    std::cout << e.what() << '\n';
}