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



struct Combatant
{
    int hitPoints;
    int damage;
    int armour;
};

const Combatant initialBoss
{
    100,8,2
};


bool fight(Combatant you,  Combatant boss)
{
    while(    you.hitPoints  > 0
          &&  boss.hitPoints > 0)
    {
        if(you.hitPoints > 0)
        {
            auto damage = std::max(1, you.damage - boss.armour);

            boss.hitPoints-=damage;
        }

       
        if(boss.hitPoints > 0)
        {
            auto damage = std::max(1, boss.damage - you.armour);

            you.hitPoints-=damage;
        }

    }

    return you.hitPoints > 0;
}



struct Weapon
{
    int cost;
    int damage;
} const weapons[]
{
    { 8,4},
    {10,5},
    {25,6},
    {40,7},
    {74,8},
};

struct Armour
{
    int cost;
    int armour;
} const armours[]
{
    {  0,0},
    { 13,1},
    { 31,2},
    { 53,3},
    { 75,4},
    {102,5},
};


struct Ring
{
    int cost;
    int damage;
    int armour;

    auto operator<=>(Ring const &) const noexcept = default;

} const rings[]
{
    {   0,0,0},

    {  25,1,0},
    {  50,2,0},
    { 100,3,0},

    {  20,0,1},
    {  40,0,2},
    {  80,0,3},
};


struct Equipment
{
    int cost;
    int damage;
    int armour;

    auto operator<=>(Equipment const &) const noexcept = default;
};


int main()
try
{

    std::vector<Equipment>  loadouts;


    for(auto &weapon : weapons)
    {
        for(auto &armour : armours)
        {
            for(auto &ring1 : rings)
            {
                for(auto &ring2 : rings)
                {
                    if(    ring1 != ring2
                       ||  ring1 == rings[0])
                    {
                        loadouts.emplace_back(weapon.cost  +armour.cost  +ring1.cost  +ring2.cost,
                                              weapon.damage+              ring1.damage+ring2.damage,
                                                            armour.armour+ring1.armour+ring2.armour);
                    }
                }
            }
        }
    }

    std::ranges::sort(loadouts);    
    
    
    for(auto &loadout : loadouts)
    {
        if(fight( { 100, loadout.damage, loadout.armour}, initialBoss))
        {
            std::cout << "part 1 : " << loadout.cost << " gold\n";

            break;
        }
    }

    std::ranges::reverse(loadouts);


    for(auto &loadout : loadouts)
    {
        if(!fight( { 100, loadout.damage, loadout.armour}, initialBoss))
        {
            std::cout << "part 2 : " << loadout.cost << " gold\n";

            break;
        }
    }




    return 0;
}
catch(std::exception const &e)
{
    std::cout << e.what() << '\n';
}