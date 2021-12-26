#include <cassert>
#include <cstdint>

#include <array>

#include <fstream>
#include <iostream>
#include <format>


using namespace std::literals;
#include "include/thrower.h"


// To continue, please consult the code grid in the manual.  Enter the code at row 2978, column 3083.

std::array<std::array<int64_t,6200>,6200> grid{};

int main()
try
{
    int64_t sequence=20151125;

    for(int row=0;row<6200;row++)
    {
        int r=row;
        int c=0;

        while(r >= 0)
        {
            grid[r][c]=sequence;            
            sequence *= 252533;
            sequence %= 33554393;

            if(sequence==0)
            {
                std::cout << "Zero!\n";
            }
            r--;
            c++;
        }
    }



    std::ofstream numbers{"grid.txt"};

    for(int row=3000;row<3100;row++)
    {
        for(int column=3000;column<3100;column++)
        {
            numbers << std::format("{:>8} ",grid[row][column]);
        }
        numbers << "\n";
    }


    std::cout << "Part 1 : " << grid[2978-1][3083-1] << "\n";

    return 0;
}
catch(std::exception const &e)
{
    std::cout << e.what() << '\n';
}