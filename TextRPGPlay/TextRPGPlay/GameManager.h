#pragma once

#include "Character.h"
#include "Monster.h"

class GameManager {
public:
    GameManager();

    Character* player;

    Monster* GenerateMonster(int level);
    Monster* GenerateBossMonster(int level);

    void Battle(Character* player, Monster* monster);
    void DisplayInventory(Character* player);
    void Run();
};