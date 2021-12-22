#include <cassert>
#include <cstdint>

#include <string>
#include <vector>

#include <iostream>
#include <sstream>
#include <format>
#include <memory>

#include <algorithm>
#include <numeric>
#include <ranges>

#include <chrono>




using namespace std::literals;
#include "include/thrower.h"
#include "include/stopwatch.h"

#include "wrap_wincrypt.h"
#include "wrap_bcrypt.h"

//using namespace WinCrypt;
using namespace BCrypt;


std::string const input{"ckczppom"s};







std::string md5(std::string const &s)
{
    Hash        hasher;    

    hasher.append(s);

    return hasher.digest();
}

 
int part1(std::string const &s)
{
    int i{-1};
    std::string candidate;

    do
    {
        i++;
        candidate = input+std::to_string(i);
       
    } while(!md5(candidate).starts_with("00000"));

    return i;
}

int part2(std::string const &s)
{
    int i{-1};
    std::string candidate;

    do
    {
        i++;
        candidate = input+std::to_string(i);
    } while(!md5(candidate).starts_with("000000"));

    return i;
}



int main()
try
{
    assert(md5("abcdef") ==  "e80b5017098950fc58aad83c8c14978e");
    assert(md5(input)    ==  "597bb7cda92b70698b3a70ad93920b8e");

    assert(part1("abcdef") == 609043); 

    Stopwatch   sw;
    std::cout << std::format("Part 1 : {} ",part1(input));
    std::cout << std::format(" {} \n",  sw.seconds());

    sw.reset();
    std::cout << std::format("Part 2 : {} ",part2(input));
    std::cout << std::format(" {} \n",  sw.seconds());

    return 0;
}
catch(std::exception const &e)
{
    std::cout << e.what() << '\n';
}