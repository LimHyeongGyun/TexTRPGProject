#pragma once

#include <string>
#include "Monster.h"

using namespace std;

class Character;
class Inventory;
class Forge;
class Store;

enum class PlayState {
    Idle,
    Battle,
    End
};
class GameManager {
private:
    static GameManager* instance;
public:
    GameManager();
    static GameManager& Get();
    GameManager(const GameManager&) = delete;
    GameManager& operator=(const GameManager&) = delete;

    PlayState playState = PlayState::Idle;

    void Run();
    void Menu(PlayState playState);//�޴�
    void IdleBehavior(); //������ �ൿ
    void SetStage(); //�������� ����
    Monster* GenerateMonster(int level);//���� ����
    void Battle(Character* character, Monster* monster);//���� �ݺ�
    string WrongInputMessage();
};