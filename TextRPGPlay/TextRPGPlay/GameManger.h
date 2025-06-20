#pragma once

class Character;
class Monster;
class BossMonster;

class GameManager {
public:
    GameManager();
    Character* player;

    Monster* GenerateMonster(int level);
    BossMonster* GenerateBossMonster(int level);

    void Battle(Character* player, Monster* monster);
    void DisplayInventory(Character* player);
    void Run();
};
