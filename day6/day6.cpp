#include <cassert>
#include <cstdint>

#include <string>
#include <vector>

#include <iostream>
#include <sstream>
#include <string_view>
#include <format>

#include <algorithm>
#include <numeric>
#include <ranges>

using namespace std::literals;
#include "include/thrower.h"

extern std::istringstream realData;

enum class Operation
{
    set,
    reset,
    toggle
};

struct Location
{
    int row;
    int column;
};

struct Instruction
{
    Operation operation;

    Location    start;
    Location    end;
};



Instruction parseLine(std::string_view  line)
{
    Instruction instruction{};

    if(line.starts_with("turn on"))
    {
        instruction.operation = Operation::set;
        line.remove_prefix(8);
    }
    else if(line.starts_with("turn off"))
    {
        instruction.operation = Operation::reset;
        line.remove_prefix(9);
    }
    else if(line.starts_with("toggle"))
    {
        instruction.operation = Operation::toggle;
        line.remove_prefix(7);
    }
    else
    {
        throw_runtime_error("bad instruction");
    }


    std::istringstream  stream{std::string{line}};

    char comma{};

    if(! (stream >> instruction.start.row >> comma >> instruction.start.column))
    {
        throw_runtime_error("bad start");
    }

    std::string through;
    stream >> through;
    assert(through=="through");

    if(! (stream >> instruction.end.row >> comma >> instruction.end.column))
    {
        throw_runtime_error("bad end");
    }

    return instruction;
}

void part1(auto const &instructions)
{
    std::array<std::array<bool,1000>,1000> lights{};

    for(auto const &instruction : instructions)
    {
        for(int row=instruction.start.row; row <= instruction.end.row; row++)
        {
            for(int column=instruction.start.column; column <= instruction.end.column; column++)
            {
                switch(instruction.operation)
                {
                case Operation::set:        
                    lights[row][column]=true;
                    break;

                case Operation::reset:        
                    lights[row][column]=false;
                    break;

                case Operation::toggle:        
                    lights[row][column]=!lights[row][column];
                    break;
                }

            }
        }
    }


    int count{};

    for(auto &row : lights)
    {
        for(auto light : row)
        {
            if(light)
            {
                count++;
            }
        }
    }

    std::cout << "Part 1 " << count << "\n";
}


void part2(auto const &instructions)
{
    std::array<std::array<uint8_t,1000>,1000> lights{};

    for(auto const &instruction : instructions)
    {
        for(int row=instruction.start.row; row <= instruction.end.row; row++)
        {
            for(int column=instruction.start.column; column <= instruction.end.column; column++)
            {
                switch(instruction.operation)
                {
                case Operation::set:        
                    lights[row][column]++;
                    assert(lights[row][column]);
                    break;

                case Operation::reset:        
                    if(lights[row][column])
                    {
                        lights[row][column]--;
                    }
                    break;

                case Operation::toggle:        
                    lights[row][column]+=2;
                    assert(lights[row][column] > 1);
                    break;
                }

            }
        }
    }


    int total{};

    for(auto &row : lights)
    {
        for(auto light : row)
        {
            total+=light;
        }
    }

    std::cout << "Part 2 " << total<< "\n";
}



int main()
try
{
    std::vector<Instruction> instructions;
    std::string             line;
    

    while(std::getline(realData,line))
    {
        instructions.push_back(parseLine(line));
    }

    part1(instructions);
    part2(instructions);


    return 0;
}
catch(std::exception const &e)
{
    std::cout << e.what() << '\n';
}