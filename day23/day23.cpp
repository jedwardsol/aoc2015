#include <cassert>
#include <cstdint>

#include <array>
#include <vector>

#include <iostream>
#include <sstream>
#include <format>


using namespace std::literals;
#include "include/thrower.h"

extern std::istringstream data;


struct Instruction
{
    enum class OpCode : int8_t
    {
        HLF,        // half             r
        TPL,        // triple           r
        INC,        // increment        r
        JMP,        //                  o
        JIE,        // jump if even     r,o
        JIO,        // jump if one      r,o
    };


    OpCode      opcode{};   
    int8_t      reg{-1};
    int8_t      operand{};
};

using Program=std::vector<Instruction>;


struct Computer
{
    Computer(Program program) : program{std::move(program)}
    {}

    void run()
    {
        while(pc < program.size())
        {
            auto const &instruction = program[pc];

            switch(instruction.opcode)
            {
            case Instruction::OpCode::HLF:
                registers[ instruction.reg] /=2;
                pc++;
                break;

            case Instruction::OpCode::TPL:
                registers[ instruction.reg] *=3;
                pc++;
                break;

            case Instruction::OpCode::INC:
                registers[ instruction.reg]++;
                pc++;
                break;

            case Instruction::OpCode::JMP:
                pc+=instruction.operand;
                break;

            case Instruction::OpCode::JIE:

                if(registers[instruction.reg] % 2 == 0)
                {
                    pc+=instruction.operand;
                }
                else
                {
                    pc++;
                }
                break;

            case Instruction::OpCode::JIO:

                if(registers[instruction.reg] == 1)
                {
                    pc+=instruction.operand;
                }
                else
                {
                    pc++;
                }
                break;

            default:
                throw_runtime_error("bad instruction");
            }
        }
    }

    Program                     program;
    std::array<uint64_t,2>      registers{};
    size_t                      pc{};
    
};


auto readInstruction(std::string  const &line)
{
    Instruction         instruction;

    std::istringstream  stream{line};

    std::string         token1;
    std::string         token2;
    
    stream >> token1 >> token2;

    if(token1 == "hlf")
    {
        instruction.opcode = Instruction::OpCode::HLF;
        instruction.reg    = token2[0]-'a';
    }
    else if(token1 == "tpl")
    {
        instruction.opcode = Instruction::OpCode::TPL;
        instruction.reg    = token2[0]-'a';
    }
    else if(token1 == "inc")
    {
        instruction.opcode = Instruction::OpCode::INC;
        instruction.reg    = token2[0]-'a';
    }
    else if(token1 == "jmp")
    {
        instruction.opcode = Instruction::OpCode::JMP;
        instruction.operand= stoi(token2);
    }
    else if(token1 == "jie")
    {
        std::string token3;
        stream >> token3;

        instruction.opcode = Instruction::OpCode::JIE;
        instruction.reg    = token2[0]-'a';
        instruction.operand= stoi(token3);
    }
    else if(token1 == "jio")
    {
        std::string token3;
        stream >> token3;

        instruction.opcode = Instruction::OpCode::JIO;
        instruction.reg    = token2[0]-'a';
        instruction.operand= stoi(token3);
    }
    else
    {
        throw_runtime_error("Bad instruction");
    }

    return instruction;
}

auto readProgram()
{
    Program     program;
    std::string line;

    while(std::getline(data,line))
    {
        if(line.size())
        {
            Instruction i = readInstruction(line);

            program.push_back(i);
        }
    }

    return program;
}

int main()
try
{
    auto program = readProgram();

    Computer    computer1{program};
    computer1.run();
    std::cout << "Part 1 : " << computer1.registers[1] << "\n";   // register b

    Computer    computer2{program};

    computer2.registers[0]=1;       // register a to 1
    computer2.run();
    std::cout << "Part 1 : " << computer2.registers[1] << "\n";   // register b



    return 0;
}
catch(std::exception const &e)
{
    std::cout << e.what() << '\n';
}