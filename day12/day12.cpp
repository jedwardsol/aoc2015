#include <cassert>
#include <cstdint>

#include <string>
#include <vector>

#include <fstream>
#include <iostream>
#include <sstream>
#include <format>

#include <algorithm>
#include <numeric>
#include <ranges>

#include <boost/json.hpp>

using namespace std::literals;
#include "include/thrower.h"

extern std::istringstream realData;


boost::json::value loadFile( )
{
    std::ifstream               file{"data12.json"};
    std::string                 data;

    std::getline(file,data);

    if(data.empty())
    {
        throw_runtime_error("no data");
    }

    boost::json::stream_parser  parser;

    parser.write(data.c_str());
    parser.finish();

    return parser.release();
}


bool isRed(boost::json::value const &object)
{
    for(auto &element : object.get_object())
    {
        if(element.value().kind()==boost::json::kind::string)
        {
            auto const &string = element.value().as_string();

            if(string=="red")
            {
                return true;
            }
        }
    }

    return false;
}



int64_t sumNumbers(boost::json::value const &value, bool ignoreReds)
{
    int64_t sum{};

    switch(value.kind())
    {
    case boost::json::kind::object:
    {
        if(   ignoreReds
           && isRed(value.get_object()))
        {
            // ignore
        }
        else
        {
            for(auto &element : value.get_object())
            {
                sum += sumNumbers( element.value(), ignoreReds);
            }
        }

        break;
    }

    case boost::json::kind::array:
    {
        for(auto &element : value.get_array())
        {
            sum += sumNumbers(element,ignoreReds);
        }
        break;
    }


    case boost::json::kind::uint64:
        sum+=value.get_uint64();
        break;

    case boost::json::kind::int64:
        sum+=value.get_int64();
        break;

    case boost::json::kind::string:
        break;

    default:
        throw_runtime_error("type!");
        break;
    }

    return sum;
}



int main()
try
{
    auto document = loadFile();

    auto part1    = sumNumbers(document,false);
    auto part2    = sumNumbers(document,true);

    std::cout << "Part 1 : " << part1 << "\n";
    std::cout << "Part 2 : " << part2 << "\n";

    return 0;
}
catch(std::exception const &e)
{
    std::cout << e.what() << '\n';
}