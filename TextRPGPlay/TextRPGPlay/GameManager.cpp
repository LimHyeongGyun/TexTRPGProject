#include "GameManager.h"
#include "Goblin.h"
#include "Orc.h"
#include "Troll.h"
#include "Slime.h"
#include "Dragon.h"
#include "Inventory.h"
#include "ItemManager.h"
#include "Item.h"
#include "Character.h"
#include "Forge.h"
#include <iostream>
#include <vector>
#include <limits>
#include "Store.h"

using namespace std;

GameManager* GameManager::instance = nullptr;

GameManager::GameManager() {}

GameManager& GameManager::Get()
{
    if (instance == nullptr)
    {
        instance = new GameManager();
    }
    return *instance;
}

void GameManager::Run()
{
    playState = PlayState::Idle; //대기상태
    IdleBehavior();
}

void GameManager::Menu(PlayState playState)
{
    if (playState == PlayState::Idle)
    {
        cout << "\n==== [대기] ====\n";
        cout << "0.플레이어 스탯 확인\n";
        cout << "1. 인벤토리 확인\n";
        cout << "2. 대장간 방문\n";
        cout << "3. 상점 방문\n";
        cout << "4. 전투 진행\n";
    }
    else if (playState == PlayState::Battle)
    {
        cout << "\n==== [전투]행동을 선택하세요 ====\n";
        cout << "1. 공격\n";
        cout << "2. 아이템 사용\n";
        cout << "3. 도망가기\n";
    }
}

void GameManager::IdleBehavior()
{
    while (true) {
        Menu(playState);
        cout << "입력 >> ";

        int choice;
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << WrongInputMessage();
            continue;
        }

        switch (choice)
        {
            case 0:
                Character::Get().DisplayStatus(); //플레이어 스탯 확인
                break;
            case 1:
                Inventory::Get().DisplayInventory(); //인벤토리 확인
                break;
            case 2:
            {
                Forge forge;
                forge.EnteredForge(); //대장간 진입
                break;
            }
            case 3:
                Store::Get().EnteredStore(); //상점 진입
                break;
            case 4:
                SetStage();
                return;
            default:
                cout << WrongInputMessage();
                break;
        }
    }
}

Monster* GameManager::GenerateMonster(int level)
{
    Monster* spawnMonster = nullptr;
    if (level <= 3) spawnMonster = new Slime(level);
    else if (level <= 5) spawnMonster = new Orc(level);
    else if (level <= 7) spawnMonster = new Troll(level);
    else if (level <= 9) spawnMonster = new Goblin(level);
    else if (level >= 10) spawnMonster = new Dragon(level);
    return spawnMonster;
}

void GameManager::SetStage()
{
    Character& player = Character::Get();

    int level = player.GetLevel();
    Monster* monster = GenerateMonster(level);

    player.DisplayStatus(); //플레이어 상태 표시

    cout << "\n===== 스테이지 정보 =====" << endl;
    cout << monster->getName() << " 등장!" << endl;
    cout << monster->getName() << " 체력: " << monster->getHealth() << endl;
    cout << monster->getName() << " 공격력 : " << monster->Attack() << endl; //스테이지 몬스터 정보

    cout << "\n===============================" << endl;
    cout << "========== 전투 시작 ==========" << endl;
    cout << "===============================" << endl;
    playState = PlayState::Battle;
    Battle(&player, monster); //전투 시작
}

void GameManager::Battle(Character* player, Monster* monster)
{
    //전투진행
    while (player->GetHealth() > 0 && monster->getHealth() > 0)
    {
        Menu(playState);
        cout << "입력 >> ";

        int choice;
        cin >> choice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "잘못된 입력입니다.\n";
            continue;
        }

        if (choice == 1)
        {
            int damage = player->Attack();
            cout << player->GetName() << "이(가) " << monster->getName() << "을(를) 공격!" << endl;

            monster->takeDamage(damage);
            cout << "몬스터 체력 : " << monster->getHealth() << endl;
        }
        else if (choice == 2)
        {
            player->UseItem();
            continue;
        }
        else if (choice == 3)
        {
            cout << "도망쳤습니다!\n";
            return;
        }
        else
        {
            cout << "잘못된 입력입니다.\n";
            continue;
        }

        if (monster->getHealth() > 0)
        {
            int mDamage = monster->Attack();
            cout << "몬스터" << monster->getName() << "의 공격! " << endl;

            player->TakeDamage(mDamage);
            cout << player->GetName() << " 체력: " << player->GetHealth() << endl;
        }
        else
        {
            break; //전투 탈출
        }
    }

    if (player->GetHealth() > 0) {
        playState = PlayState::Idle; //대기상태 변경
        cout << "\n전투 승리!" << endl;

        Item* dropItem = monster->ItemDrop(); //몬스터 아이템 드랍
        int dropExp = monster->getExpDrop(); //몬스터 경험치 드랍
        int dropGold = monster->getGoldDrop(); //몬스터 골드 드랍

        player->GetExperience(dropExp); //경험치 획득
        player->BorrowGold(dropGold); //골드 획득
        cout << "경험치: " << dropExp << "획득" << endl;
        cout << "골드: " << dropGold << "획득" << endl; //획득한 경험치와 골드

        if (dropItem) {
            vector<Item*> dropItems = { dropItem };
            player->GetItem(dropItems); //플레이어 아이템 획득
        }
        
        cout << "\n===== 캐릭터 현재 상태 =====\n";
        player->DisplayStatus(); 
    }
    else {
        playState = PlayState::End;
        Character::Get().Die(); //플레이어 사망
        system("pause");
        return;
    }

    if (string(monster->getName()) == "Dragon") {
        cout << "\n드래곤을 처치했습니다. 게임 클리어!\n";
        delete monster;
        system("pause");
        exit(0); // 프로그램 종료
    }

    delete monster;
    IdleBehavior();
}

string GameManager::WrongInputMessage()
{
    return "잘못된 입력입니다.\n";
}