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



int main()
try
{
    {
        auto floor = std::ranges::count(realData,'(') - std::ranges::count(realData,')');
        std::cout << "Part 1 : " << floor << "\n";
    }

    {
        int floor{};

        for(auto i=0u;i<realData.size();i++)
        {
            floor += realData[i]=='(' ? 1 : -1;

            if(floor == -1)
            {
                std::cout << "Part 2 : " << i+1 << "\n";
                break;
            }
        }

    }

    return 0;
}
catch(std::exception const &e)
{
    std::cout << e.what() << '\n';
}