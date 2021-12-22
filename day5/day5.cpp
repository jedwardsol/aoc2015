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

using namespace std::literals;
#include "include/thrower.h"



bool isNice1(std::string const &s)
{
// rule 1 : 3 vowels

    auto isVowel=[](char c)
    {
        return c=='a' || c=='e' || c=='i' || c=='o' || c=='u';
    } ;

    auto vowels = std::ranges::count_if(s, isVowel);

    if(vowels < 3)
    {
        return false;
    }


// rule 2 - a pair of identical letters

    bool doubleLetter{false};
    
    for(int i=0;i<s.size()-1;i++)
    {
        if(s[i]==s[i+1])
        {
            doubleLetter=true;
            break;
        }
    }

    if(!doubleLetter)
    {
        return false;
    }


// rule 3 - no forbidden substrings

    if(   s.find("ab") != s.npos
       || s.find("cd") != s.npos
       || s.find("pq") != s.npos
       || s.find("xy") != s.npos)
    {
        return false;
    }

    return true;
}



bool isNice2(std::string const &s)
{
// rule 1 : identical letters,  separated by any letter  (aba or aaa)

    bool aBa{false};
    
    for(int i=0;i<s.size()-2;i++)
    {
        if(s[i]==s[i+2])
        {
            aBa=true;
            break;
        }
    }

    if(!aBa)
    {
        return false;
    }

// rule 2 : repeated pair (aaxaa)

    bool pairFound{false};

    for(int i=0;i<s.size()-2;i++)
    {
        auto pair = std::string_view{&s[i],2};

        if(s.find(pair,i+2) != s.npos)
        {
            pairFound=true;
            break;
        }
    }

    if(!pairFound)
    {
        return false;
    }

    return true;
}



int main()
try
{
    std::ifstream  file{"data5.txt"};

    if(!file)
    {
        throw_runtime_error("no file");
    }

    std::vector<std::string>    lines;
    std::string line;
    
    while(std::getline(file,line))
    {
        lines.push_back(line);
    }


    std::cout << std::format("Part 1 : {}\n",std::ranges::count_if(lines, isNice1));
    std::cout << std::format("Part 2 : {}\n",std::ranges::count_if(lines, isNice2));


    return 0;
}
catch(std::exception const &e)
{
    std::cout << e.what() << '\n';
}