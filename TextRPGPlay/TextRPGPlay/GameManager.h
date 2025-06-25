#pragma once

#include "Monster.h"

class Character;
class Inventory;

class GameManager {
private:
    static GameManager* instance;
public:
    GameManager();
    static GameManager& Get();
    GameManager(const GameManager&) = delete;
    GameManager& operator=(const GameManager&) = delete;

    Monster* GenerateMonster(int level);
    Monster* GenerateBossMonster(int level);

    void Battle(Character* character, Monster* monster);
    void DisplayInventory();
    void Run();
    std::string WrongInputMessage();
};