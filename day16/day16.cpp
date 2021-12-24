#include <cassert>
#include <cstdint>

#include <array>
#include <vector>
#include <map>

#include <fstream>
#include <iostream>
#include <sstream>
#include <format>

#include <algorithm>
#include <numeric>
#include <ranges>

using namespace std::literals;
#include "include/thrower.h"



struct Aunt
{
    std::map<std::string,int>   properties; // name -> count

    bool    matches(Aunt  &other)
    {
        for(auto &[name, number] : properties)
        {
            assert(other.properties.contains(name));

            if(other.properties[name] != number)
            {
                return false;
            }
        }

        return true;
    }

};


auto readAunt(std::istringstream line)
{
    Aunt            aunt;

    std::string     token1;
    std::string     token2;

    std::getline(line,token1,':');       // read name


    while(   std::getline(line,token1,':')
          && std::getline(line,token2,','))
    {
        while(token1.front()==' ')
        {
            token1.erase(token1.begin());
        }

        aunt.properties[token1] = stoi(token2);
    }

    return aunt;
}

auto readAunts()
{
    std::map<int,Aunt> aunts;       // Sue number -> info

    std::ifstream   data{"data16.txt"};

    for(int i=1;i<500;i++)
    {
        std::string line;
        
        std::getline(data,line);

        aunts[i]=readAunt(std::istringstream{line});
    }

    return aunts;
}




int main()
try
{
    auto aunts=readAunts();


    Aunt    gifter  
    {
        {{"children", 3},
        {"cats", 7},
        {"samoyeds", 2},
        {"pomeranians", 3},
        {"akitas", 0},
        {"vizslas", 0},
        {"goldfish", 5},
        {"trees", 3},
        {"cars", 2},
        {"perfumes", 1}},
    };

    for(auto &[number, aunt] : aunts)
    {
        if(aunt.matches(gifter))
        {
            std::cout << "Part 1 : " << number << "\n";
        }
    }



    return 0;
}
catch(std::exception const &e)
{
    std::cout << e.what() << '\n';
}