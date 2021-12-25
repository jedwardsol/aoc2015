#include <cassert>
#include <cstdint>

#include <array>
#include <vector>
#include <deque>

#include <iostream>
#include <sstream>
#include <format>

#include <algorithm>
#include <numeric>
#include <ranges>

using namespace std::literals;
#include "include/thrower.h"
#include "include/console.h"

extern std::istringstream testData;
extern std::istringstream realData;

template <size_t N, bool StuckCorners>
struct Conway
{
    using Grid = std::array<std::array<bool,N+2>,N+2>;

    Grid    one{};
    Grid    two{};

    Grid    *read;
    Grid    *write;
    Console  console;

    Conway(std::istringstream &initialState) : read{&one}, write{&two}
    {
        initialState.clear();
        initialState.seekg(0);

        std::string line;

        for(int row=1;row<=N;row++)
        {
            std::getline(initialState,line);

            assert(line.size()==N);

            for(int column=1;column<=N;column++)
            {
                one[row][column] = (line[column-1] == '#');
            }
        }
    }

    void draw()
    {
        console.clear();
        console.goTo(1,1);

        std::string output;

        for(auto &row : (*read))
        {
            for(auto light : row)
            {
                output +=  (light ? 'O' : '.');
            }
            output += '\n';
        }

        std::cout << output;
        Sleep(50);
    }

    int count(int row, int column)
    {
        int count{};

        for(int dr : {-1,0,1})
        {
            for(int dc : {-1,0,1})
            {
                if(dc || dr)
                {
                    if((*read)[row+dr][column+dc])
                    {
                        count++;
                    }
                }
            }
        }

        return count;
    }

    int count()
    {
        int count{};

        for(int row=1;row<=N;row++)
        {
            for(int column=1;column<=N;column++)
            {
                if((*read)[row][column])
                {
                    count++;
                }
            }
        }

        return count;
    }


    void evolve()
    {
        for(int row=1;row<=N;row++)
        {
            for(int column=1;column<=N;column++)
            {
                int  neighbours = count(row,column);
                bool on         = (*read)[row][column];

                if(on)
                {
                    (*write)[row][column] =  (neighbours==2 || neighbours==3);
                }
                else
                {
                    (*write)[row][column] =  (neighbours==3);
                }
            }
        }

        if constexpr(StuckCorners)
        {
            (*write)[1][1] =  true;
            (*write)[1][N] =  true;
            (*write)[N][1] =  true;
            (*write)[N][N] =  true;
        }

        
        std::swap(read,write);
    }


};



int main()
try
{
/*
    Conway<6>  lights{testData};

    lights.draw();
    lights.evolve();
    lights.draw();
    lights.evolve();
    lights.draw();

        return 0;

*/
    {
        Conway<100,false>  lights{realData};

        for(int i=0;i<100;i++)
        {
            lights.evolve();
            lights.draw();
        }

        std::cout << "part 1 : " << lights.count() << "\n";
    }

    {
        Conway<100,true>  lights{realData};

        for(int i=0;i<100;i++)
        {
            lights.evolve();
            lights.draw();
        }

        std::cout << "part 2 : " << lights.count() << "\n";
    }


    return 0;
}
catch(std::exception const &e)
{
    std::cout << e.what() << '\n';
}