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
#include "include/stopwatch.h"

auto const input {"1113222113"s};


std::string expand(std::string_view in)
{
    std::string result;
    result.reserve(50'000'000);

    while(!in.empty())
    {
        char  number=in.front();
        char  count{'0'};

        while(   !in.empty()
              && in.front()==number)
        {
            count++;
            in.remove_prefix(1);
        }

        assert(count < '4');

        result += count;
        result += number;
    }

    return result;
}


int main()
try
{
    assert(expand("1")      == "11");
    assert(expand("11")     == "21");
    assert(expand("21")     == "1211");
    assert(expand("1211")   == "111221");
    assert(expand("111221") == "312211");


    auto s = input;

    // 50 is small enough to just do  (7 milliseconds)
    // 75 takes 7 seconds and is 2,705,156,398

    for(int i=0;i<76;i++)
    {
        Stopwatch sw;

        s = expand(s);

        if(i==39)
        {
            std::cout << "Part 1 : " ;
        }
        else if(i==49)
        {
            std::cout << "Part 2 : " ;
        }

        {
            std::cout << std::format("{:2} : {:L} {} \n",i+1,s.size(), sw.milliseconds());
        }
    }


    return 0;
}
catch(std::exception const &e)
{
    std::cout << e.what() << '\n';
}