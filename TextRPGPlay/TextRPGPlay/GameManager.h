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
    void Menu(PlayState playState);//메뉴
    void IdleBehavior(); //대기상태 행동
    void SetStage(); //스테이지 설정
    Monster* GenerateMonster(int level);//몬스터 생성
    void Battle(Character* character, Monster* monster);//전투 반복
    string WrongInputMessage();
};