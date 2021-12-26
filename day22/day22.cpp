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


struct Boss
{
    int hitPoints;
    int damage;
};

const Boss initialBoss
{
    58,9      // day 22 input
};


enum class Spell
{
    MagicMissile, Drain,Shield,Poison,Recharge
};


struct Wizard
{
    std::deque<Spell>    spells;

    int hitPoints        {50};
    int mana             {500};

    int armour           {};   

                                    // magic missle 4 damage    (cost 53)
                                    // drain +2 damage, +2 heal (cost 73)
    int shieldRemaining  {};        // armour +7 for 6 turns    (cost 113)
    int poisonRemaining  {};        // damage +3 for 6 turns    (cost 173)
    int rechargeRemaining{};        // mana +101 for 5 turns    (cost 229)
};



void applyEffects(Wizard &you, Boss &boss)
{
    if(you.shieldRemaining)
    {
        you.armour = 7;    
        you.shieldRemaining--;
    }
    else
    {
        you.armour = 0;    
    }

    if(you.poisonRemaining)
    {
        boss.hitPoints -= 3;    
        you.poisonRemaining--;
    }

    if(you.rechargeRemaining)
    {
        you.mana += 101;    
        you.rechargeRemaining--;
    }
}


bool fight(Wizard you,  Boss boss)
{
    while(    you.hitPoints  > 0
          &&  boss.hitPoints > 0)
    {

// your turn

        if(you.hitPoints > 0)
        {
            applyEffects(you,boss);

            if(boss.hitPoints < 1)
            {
                return true;
            }


            switch(you.spells.front())
            {
            case Spell::MagicMissile:
                you.mana        -= 53;
                boss.hitPoints  -= 4;
                break;

            case Spell::Drain:
                you.mana        -= 73;
                boss.hitPoints  -= 2;
                you.hitPoints   +=2;
               
                break;

            case Spell::Shield:
                you.mana        -= 113;
                
                if(you.shieldRemaining == 0)
                {
                    you.shieldRemaining = 6;
                }
                break;

            case Spell::Poison:
                you.mana        -= 173;
                
                if(you.poisonRemaining == 0)
                {
                    you.poisonRemaining = 6;
                }
                break;

            case Spell::Recharge:
                you.mana        -= 229;
                
                if(you.rechargeRemaining == 0)
                {
                    you.rechargeRemaining = 5;
                }
                break;
            }

            if(you.mana < 1)
            {
                return false;
            }


            you.spells.pop_front();
        }

//  boss's turn
       
        if(boss.hitPoints > 0)
        {
            applyEffects(you,boss);

            if(boss.hitPoints < 1)
            {
                return true;
            }

            auto damage = std::max(1, boss.damage - you.armour);
            you.hitPoints-=damage;
        }
    }

    return you.hitPoints > 0;
}




int main()
try
{
    assert( fight( {{Spell::Poison,  Spell::MagicMissile}, 10,250},{13,8}));       // example the player wins 
    assert( fight( {{Spell::Recharge,
                     Spell::Shield, 
                     Spell::Drain, 
                     Spell::Poison,
                     Spell::MagicMissile},10,250},{14,8}));       // example the player wins 


    return 0;
}
catch(std::exception const &e)
{
    std::cout << e.what() << '\n';
}