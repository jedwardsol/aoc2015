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


std::string const &nextCandidate()
{
    static auto password{"hxbxwxba"s};

    if(password == "zzzzzzzz")
    {
        throw_runtime_error("no more passwords");
    }
    
    for(int i=7;i>0;i--)
    {
        password[i]++;

        if(password[i] <= 'z')
        {
            break;
        }
        else
        {
            password[i] = 'a';
        }
    }
    
    return password;
}




bool forbidden(std::string const &password)
{
// rule 2 : no i o l

    for(auto c: password)
    {
        if(c=='i' || c=='o' || c=='l')
        {
            return true;
        }
    }

// rule 1 : must have sequence of 3 consecutive letters
    bool sequenceFound{};

    for(int i=0;i<6;i++)
    {
        if(   password[i]+1 == password[i+1]
           && password[i]+2 == password[i+2])
        {
            sequenceFound=true;
        }
    }

    if(!sequenceFound)
    {
        return true;
    }

// rule 3 : must contain 2 different pairs

    int pairCount{};

    for(char c = 'a'; c<='z'; c++)
    {
        char pair[2] {c,c};

        if(password.find(pair,0,2)!=password.npos)
        {
            pairCount++;
        }
    }

    if(pairCount<2)
    {
        return true;
    }

    return false; // password ok
}

std::string nextPassword()
{
    std::string password;       // TODO eliminate copy properly

    do
    {
        password = nextCandidate();
    } while(forbidden(password));

    return password;
}


int main()
try
{
    std::cout << std::format("Part 1 : {}\n",nextPassword());
    std::cout << std::format("Part 2 : {}\n",nextPassword());

    return 0;
}
catch(std::exception const &e)
{
    std::cout << e.what() << '\n';
}