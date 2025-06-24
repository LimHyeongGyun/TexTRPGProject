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
#include <iostream>
#include <vector>
#include <limits>

using namespace std;

GameManager::GameManager() {}

Slime* GenerateSlime(int level) { return new Slime(level); }
Orc* GenerateOrc(int level) { return new Orc(level); }
Troll* GenerateTroll(int level) { return new Troll(level); }
Goblin* GenerateGoblin(int level) { return new Goblin(level); }
Dragon* GenerateDragon(int level) { return new Dragon(level); }

void GameManager::Run() {
    Character& player = Character::Get();

    while (player.GetHealth() > 0 && player.GetLevel() < 10) {
        cout << "\n===== 캐릭터 상태 =====" << endl;
        player.DisplayStatus();

        cout << "\n===== 전투 시작 (레벨: " << player.GetLevel() << ") =====" << endl;

        int level = player.GetLevel();
        Monster* monster = nullptr;

        if (level <= 3) monster = GenerateSlime(level);
        else if (level <= 5) monster = GenerateOrc(level);
        else if (level <= 7) monster = GenerateTroll(level);
        else monster = GenerateGoblin(level);

        cout << monster->getName() << " 등장! 체력: " << monster->getHealth()
            << ", 공격력: " << monster->Attack() << endl;

        Battle(&player, monster);
        delete monster;

        if (player.GetHealth() <= 0) break;
    }

    if (player.GetHealth() > 0 && player.GetLevel() >= 10) {
        cout << "\n===== 보스 몬스터 등장 =====" << endl;
        player.DisplayStatus();

        Monster* boss = GenerateDragon(player.GetLevel());

        cout << boss->getName() << " 등장! 체력: " << boss->getHealth()
            << ", 공격력: " << boss->Attack() << endl;

        Battle(&player, boss);
        delete boss;

        if (player.GetHealth() > 0) {
            cout << "\n축하합니다! 보스를 물리치고 게임을 클리어했습니다!" << endl;
        }
        else {
            cout << "\n보스에게 패배했습니다. 게임 오버." << endl;
        }
    }

    cout << "\n게임 종료. 메모리 정리 중..." << endl;
}

void GameManager::Battle(Character* player, Monster* monster) {
    while (player->GetHealth() > 0 && monster->getHealth() > 0) {
        cout << "\n==== 행동을 선택하세요 ====\n";
        cout << "1. 공격\n";
        cout << "2. 아이템 사용\n";
        cout << "3. 도망가기\n";
        cout << "입력 >> ";

        int choice;
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "잘못된 입력입니다.\n";
            continue;
        }

        if (choice == 1) {
            int damage = player->Attack();
            monster->takeDamage(damage);
            cout << player->GetName() << "이(가) " << monster->getName()
                << "을(를) 공격! 몬스터 체력: " << monster->getHealth() << endl;
        }
        else if (choice == 2) {
            Inventory::Get().DisplayConsumeItem();
            cout << "사용할 아이템 번호 입력 >> ";
            int index;
            cin >> index;
            player->UseItem(index);
            continue;
        }
        else if (choice == 3) {
            cout << "도망쳤습니다!\n";
            return;
        }
        else {
            cout << "잘못된 선택입니다. 다시 입력하세요.\n";
            continue;
        }

        if (monster->getHealth() > 0) {
            int mDamage = monster->Attack();
            player->TakeDamage(mDamage);
            cout << monster->getName() << "의 반격! " << player->GetName()
                << " 체력: " << player->GetHealth() << endl;
        }
    }

    if (player->GetHealth() > 0) {
        cout << "\n전투 승리!" << endl;

        int exp = monster->getExpDrop();
        int gold = monster->getGoldDrop();
        player->GetExperience(exp);
        player->BorrowGold(gold);
        cout << "경험치: +" << exp << ", 골드: +" << gold << endl;

        Item* dropItem = monster->ItemDrop();
        if (dropItem) {
            vector<Item*> dropItems = { dropItem };
            player->GetItem(dropItems);
            cout << "아이템 획득: " << dropItem->GetName() << endl;
        }
    }
    else {
        cout << player->GetName() << "이(가) 사망했습니다. 게임 오버." << endl;
    }
}