#pragma once

#include <string>
#include "Monster.h"

using namespace std;

class Character;
class Inventory;
class Forge;
class Store;

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
    void PostBattleMenu();
    void Run();
    string WrongInputMessage();
};