#include <cassert>
#include <cstdint>

#include <array>
#include <vector>

#include <iostream>
#include <sstream>
#include <format>

using namespace std::literals;
#include "include/thrower.h"


struct Ingredient
{
    std::string         name;
    std::array<int,5>   properties;
    
};

std::array<Ingredient,4> const ingredients
{{
    {"Sprinkles",    {2,   0,   -2,   0,     3} },
    {"Butterscotch", {0,   5,   -3,   0,     3} },
    {"Chocolate",    {0,   0,    5,  -1,     8} },
    {"Candy",        {0,  -1,    0,   5,     8} },
}};


struct Recipe
{
    std::array<int,4>       amounts;
    std::array<int,5>       properties;
    int                     score;

};


int main()
try
{
    std::vector<Recipe> recipes;
    Recipe              recipe;


    for(recipe.amounts[0] = 1; recipe.amounts[0] <= 97; recipe.amounts[0]++)
    {
        for(recipe.amounts[1] = 1; recipe.amounts[1] <= 97 - (recipe.amounts[0] );  recipe.amounts[1]++)
        {
            for(recipe.amounts[2] = 1; recipe.amounts[2] <= 97 - (recipe.amounts[0] + recipe.amounts[1] );  recipe.amounts[2]++)
            {
                recipe.amounts[3] = 100 - (recipe.amounts[0] + recipe.amounts[1] + recipe.amounts[2]); 

                recipe.properties={};
                recipe.score     =1;                    

                for(int property = 0; property<5;property++)
                {
                    for(int ingredient=0;ingredient<4;ingredient++)
                    {
                        recipe.properties[property] += ingredients[ingredient].properties[property] * recipe.amounts[ingredient];
                    }

                    recipe.properties[property] = std::max(0, recipe.properties[property]);
                }

                recipe.score     =1;                    
                for(int property=0;property<4;property++)       // product excluding calories
                {
                    recipe.score*=recipe.properties[property];
                }

                recipes.push_back(recipe);
            }
        }
    }

    std::ranges::sort(recipes,{}, &Recipe::score);
    std::cout << std::format("part 1 : best score = {}\n",recipes.back().score);



    auto [eraseStart, eraseEnd] = std::ranges::remove_if(recipes, [](auto recipe) { return recipe.properties[4]!=500;});

    recipes.erase(eraseStart,eraseEnd);

    std::cout << std::format("part 2 : best score = {} @ 500 calories\n",recipes.back().score);


    return 0;
}
catch(std::exception const &e)
{
    std::cout << e.what() << '\n';
}