#include "GameManager.h"
#include "Monster.h" 
#include "Goblin.h"
#include "Orc.h"
#include "Troll.h"
#include "Slime.h"
#include "Dragon.h"
#include "Character.h"
#include "Inventory.h"
#include "ItemManager.h"
#include "Item.h"
#include "DropItems.h"

#include <iostream>
#include <vector>
#include <limits>

using namespace std;

GameManager::GameManager() {
    player = Character::Get("용사");
}

Monster* GameManager::GenerateMonster(int level) {
    if (level <= 3) return new Slime(level);
    else if (level <= 5) return new Orc(level);
    else if (level <= 7) return new Troll(level);
    else return new Goblin(level);
}

Monster* GameManager::GenerateBossMonster(int level) {
    return new Dragon(level);
}

void GameManager::Battle(Character* character, Monster* monster) {
    while (character->IsAlive() && monster->IsAlive()) {
        int damage = character->Attack();
        monster->takeDamage(damage);
        cout << character->GetName() << "이(가) " << monster->getName()
            << "을(를) 공격! 몬스터 체력: " << monster->getHealth() << endl;

        if (monster->IsAlive()) {
            int mDamage = monster->Attack();
            character->TakeDamage(mDamage);
            cout << monster->getName() << "의 반격! " << character->GetName()
                << " 체력: " << character->GetCurrentHealth() << endl;
        }
    }

    if (character->IsAlive()) {
        cout << "\n전투 승리!" << endl;

        int exp = monster->getExpDrop();
        int gold = monster->getGoldDrop();
        character->GetExperience(exp);
        character->BorrowGold(gold);
        cout << "경험치: +" << exp << ", 골드: +" << gold << endl;

        ItemType dropType = monster->getItemDrop();
        string dropName = monster->getItemDropName();

        Item* dropItem = ItemManager::Get().CreateItem(dropName);
        if (dropItem) {
            vector<Item*> dropItems = { dropItem };
            character->GetItem(dropItems);
            cout << "아이템 획득: " << dropItem->GetName() << endl;
        }
    }
    else {
        cout << character->GetName() << "이(가) 사망했습니다. 게임 오버." << endl;
    }

    delete monster;
}

void GameManager::DisplayInventory(Character* character) {
    Inventory::Get()->DisplayInventory();
}

void GameManager::Run() {
    while (player->IsAlive() && player->GetLevel() < 10) {
        cout << "\n===== 전투 시작 (레벨: " << player->GetLevel() << ") =====" << endl;
        Monster* monster = GenerateMonster(player->GetLevel());
        cout << monster->getName() << " 등장! 체력: " << monster->getHealth()
            << ", 공격력: " << monster->Attack() << endl;
        Battle(player, monster);

        if (!player->IsAlive()) break;

        char choice;
        cout << "인벤토리를 확인하시겠습니까? (Y/N): ";
        while (true) {
            cin >> choice;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "입력 오류입니다. Y 또는 N을 입력해주세요: ";
                continue;
            }
            if (choice == 'Y' || choice == 'y') {
                DisplayInventory(player);
                break;
            }
            else if (choice == 'N' || choice == 'n') {
                break;
            }
            else {
                cout << "잘못된 입력입니다. Y 또는 N을 입력해주세요: ";
            }
        }
    }

    if (player->IsAlive() && player->GetLevel() >= 10) {
        cout << "\n===== 보스 몬스터 등장 =====" << endl;
        Monster* boss = GenerateBossMonster(player->GetLevel());
        cout << boss->getName() << " 등장! 체력: " << boss->getHealth()
            << ", 공격력: " << boss->Attack() << endl;
        Battle(player, boss);
        delete boss;

        if (player->IsAlive()) {
            cout << "\n축하합니다! 보스를 물리치고 게임을 클리어했습니다!" << endl;
        }
        else {
            cout << "\n보스에게 패배했습니다. 게임 오버." << endl;
        }
    }

    cout << "\n게임 종료. 메모리 정리 중..." << endl;
    delete player;
    player = nullptr;
}