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

extern std::istringstream testData;
extern std::istringstream realData;


size_t countUnescaped(std::string_view line)
{
    assert(line.front() == '\"');
    assert(line.back()  == '\"');

    line.remove_prefix(1);
    line.remove_suffix(1);

    size_t   count{};

    for(auto i=0u;  i<line.size();i++)
    {
        if(line[i]=='\\')
        {
            if(   line[i+1] == '\\'
               || line[i+1] == '\"')
            {
                count++;
                i++;
            }
            else if(   line[i+1] == 'x')
            {
                count++;
                i+=3;
            }
            else
            {
                throw_runtime_error("bad escape");
            }

        }
        else
        {
            count++;
        }

    }

    return count;
}


size_t countReescaped(std::string_view line)
{
    return    2
            + line.size()
            + std::ranges::count(line,'\"')
            + std::ranges::count(line,'\\');

}



int main()
try
{
    size_t totalCode{};
    size_t totalUnescaped{};
    size_t totalReescaped{};

    std::string  line;

    while(std::getline(realData,line))
    {
        if(!line.empty())
        {
            totalCode       += line.size();
            totalUnescaped  += countUnescaped(line);
            totalReescaped  += countReescaped(line);
        }
    }

    std::cout << "Part 1 : " << totalCode-totalUnescaped << "\n";
    std::cout << "Part 2 : " << totalReescaped-totalCode  << "\n";

    return 0;
}
catch(std::exception const &e)
{
    std::cout << e.what() << '\n';
}