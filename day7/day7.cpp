#include <cassert>
#include <cstdint>

#include <string>
#include <vector>
#include <map>
#include <variant>

#include <iostream>
#include <sstream>
#include <format>

#include <algorithm>
#include <numeric>
#include <ranges>

using namespace std::literals;
#include "include/thrower.h"

extern std::istringstream realData;


using Input = std::variant<std::string,uint16_t>;

struct Wire
{
    enum class Type
    {
        Plain,
        Not,
        And,
        Or,
        LShift,
        RShift,
    };

    Type                type;
    std::array<Input,2> inputs;

};


using Circuit = std::map<std::string,Wire>;



auto tokenise(std::string const &line)
{
    std::istringstream  stream{line};
    std::string         token;

    std::vector<std::string>    tokens;

    while(stream>>token)
    {
        tokens.push_back(token);
    }

    return tokens;
}


Input parseInput(std::string const &token)
{
    try
    {
        return static_cast<uint16_t>(std::stoul(token));
    }
    catch(std::invalid_argument const &)
    {
        return token;
    }
}

auto parseLine(std::string const &line)
{
    auto        tokens = tokenise(line);
    std::string name;
    Wire        wire;

    assert(tokens.size());

    name=tokens.back();
    tokens.pop_back();
    assert(tokens.back()=="->");
    tokens.pop_back();


    switch(tokens.size())
    {
    case 1:
        wire.type       = Wire::Type::Plain;
        wire.inputs[0]  = parseInput(tokens[0]);
        break;

    case 2:
        
        if(tokens[0] == "NOT")
        {
            wire.type       = Wire::Type::Not;
            wire.inputs[0]  = parseInput(tokens[1]);
        }
        else
        {
            throw_runtime_error("unknown wire" + line);
        }
        break;

    case 3:
        
        if(tokens[1] == "AND")
        {
            wire.type       = Wire::Type::And;
        }
        else if(tokens[1] == "OR")
        {
            wire.type       = Wire::Type::Or;
        }
        else if(tokens[1] == "LSHIFT")
        {
            wire.type       = Wire::Type::LShift;
        }
        else if(tokens[1] == "RSHIFT")
        {
            wire.type       = Wire::Type::RShift;
        }
        else
        {
            throw_runtime_error("unknown wire" + line);
        }

        wire.inputs[0]  = parseInput(tokens[0]);
        wire.inputs[1]  = parseInput(tokens[2]);
        break;

    default:
            throw_runtime_error("unknown wire" + line);
    }

    return std::make_pair(name,wire);    
}


int main()
try
{
    Circuit         circuit;
    std::string     line;
    
    while(std::getline(realData,line))
    {
        circuit.insert(parseLine(line));
    }


    return 0;
}
catch(std::exception const &e)
{
    std::cout << e.what() << '\n';
}