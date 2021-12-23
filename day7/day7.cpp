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
extern std::istringstream testData;

struct Wire;
using Input = std::variant<std::string,uint16_t>;
using Circuit = std::map<std::string,Wire>;

template<class... Ts> struct overload : Ts... { using Ts::operator()...; };

struct Wire
{
    enum class Type
    {
        Invalid,
        Plain,
        Not,
        And,
        Or,
        LShift,
        RShift,
        Cached
    };

    Type                type;
    std::array<Input,2> inputs;
    std::string         name;


    uint16_t    value(Circuit &circuit)
    {
        auto evaluator = overload
        {                         
            [&](uint16_t           value) -> uint16_t { return value;},
            [&](std::string const &wire)  -> uint16_t { return circuit[wire].value(circuit);}
        };

        uint16_t    result;

        switch(type)
        {
        case Type::Cached:
            return std::get<uint16_t>(inputs[0]);

        case Type::Plain:
            result = std::visit(evaluator, inputs[0]);
            break;

        case Type::Not:
            result = ~std::visit(evaluator, inputs[0]);
            break;

        case Type::And:
            result = std::visit(evaluator, inputs[0]) & std::visit(evaluator, inputs[1]);
            break;

        case Type::Or:
            result = std::visit(evaluator, inputs[0]) | std::visit(evaluator, inputs[1]);
            break;

        case Type::LShift:
            result = std::visit(evaluator, inputs[0]) << std::visit(evaluator, inputs[1]);
            break;

        case Type::RShift:
            result = std::visit(evaluator, inputs[0]) >> std::visit(evaluator, inputs[1]);
            break;

        default:
            throw_runtime_error("Bad type");
        }

        type=Type::Cached;
        inputs[0]=result;
        return result;
    }
};





auto tokenise(std::string const &line)
{
    std::istringstream          stream{line};
    std::string                 token;
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
    Wire        wire;

    assert(tokens.size());

    wire.name=tokens.back();
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

        wire.inputs[0]  = parseInput(tokens[0]);
        wire.inputs[1]  = parseInput(tokens[2]);
        break;
    }

    assert(wire.type != Wire::Type::Invalid);

    return std::make_pair(wire.name,wire);    
}


int main()
try
{
    Circuit         circuit1;
    std::string     line;
    
    while(std::getline(realData,line))
    {
        circuit1.insert(parseLine(line));
    }

    Circuit     circuit2{circuit1};


    auto part1 = circuit1["a"].value(circuit1);
    std::cout << std::format("Part 1 : {}\n", part1);

    circuit2["b"].type      = Wire::Type::Plain;
    circuit2["b"].inputs[0] = part1;

    auto part2 = circuit2["a"].value(circuit2);
    std::cout << std::format("Part 2 : {}\n", part2);

    return 0;
}
catch(std::exception const &e)
{
    std::cout << e.what() << '\n';
}