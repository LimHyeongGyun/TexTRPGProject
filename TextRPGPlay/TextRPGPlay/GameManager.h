#pragma once

#include "Character.h"
#include "Monster.h"
#include "Inventory.h"

class GameManager {
public:
    GameManager();

    Monster* GenerateMonster(int level);
    Monster* GenerateBossMonster(int level);

    void Battle(Character* character, Monster* monster);
    void DisplayInventory();
    void Run();
};