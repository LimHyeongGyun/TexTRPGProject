#include "GameManager.h"
#include "Goblin.h"
#include "Orc.h"
#include "Troll.h"
#include "Slime.h"
#include "Dragon.h"
#include "Inventory.h"
#include "ItemManager.h"
#include "Item.h"
#include "DropItems.h"
#include <iostream>
#include <vector>
#include <limits>

using namespace std;

GameManager::GameManager() {}

Slime GenerateSlime(int level) {
    return Slime(level);
}
Orc GenerateOrc(int level) {
    return Orc(level);
}
Troll GenerateTroll(int level) {
    return Troll(level);
}
Goblin GenerateGoblin(int level) {
    return Goblin(level);
}
Dragon GenerateDragon(int level) {
    return Dragon(level);
}

void GameManager::Run() {
    Character& player = *Character::Get();

    while (player.IsAlive() && player.GetLevel() < 10) {
        cout << "\n===== 캐릭터 상태 =====" << endl;
        player.DisplayStatus();

        cout << "\n===== 전투 시작 (레벨: " << player.GetLevel() << ") =====" << endl;

        int level = player.GetLevel();
        Monster monster;
        if (level <= 3) monster = GenerateSlime(level);
        else if (level <= 5) monster = GenerateOrc(level);
        else if (level <= 7) monster = GenerateTroll(level);
        else monster = GenerateGoblin(level);

        cout << monster.getName() << " 등장! 체력: " << monster.getHealth()
            << ", 공격력: " << monster.Attack() << endl;

        Battle(player, monster);

        if (!player.IsAlive()) break;
    }

    if (player.IsAlive() && player.GetLevel() >= 10) {
        cout << "\n===== 보스 몬스터 등장 =====" << endl;
        player.DisplayStatus();

        Monster boss = GenerateDragon(player.GetLevel());

        cout << boss.getName() << " 등장! 체력: " << boss.getHealth()
            << ", 공격력: " << boss.Attack() << endl;

        Battle(player, boss);

        if (player.IsAlive()) {
            cout << "\n축하합니다! 보스를 물리치고 게임을 클리어했습니다!" << endl;
        }
        else {
            cout << "\n보스에게 패배했습니다. 게임 오버." << endl;
        }
    }

    cout << "\n게임 종료. 메모리 정리 중..." << endl;
    delete Character::Get();
}

void GameManager::Battle(Character& player, Monster& monster) {
    while (player.IsAlive() && monster.IsAlive()) {
        int damage = player.Attack();
        monster.takeDamage(damage);
        cout << player.GetName() << "이(가) " << monster.getName()
            << "을(를) 공격! 몬스터 체력: " << monster.getHealth() << endl;

        if (monster.IsAlive()) {
            int mDamage = monster.Attack();
            player.TakeDamage(mDamage);
            cout << monster.getName() << "의 반격! " << player.GetName()
                << " 체력: " << player.GetCurrentHealth() << endl;
        }
    }

    if (player.IsAlive()) {
        cout << "\n전투 승리!" << endl;

        int exp = monster.getExpDrop();
        int gold = monster.getGoldDrop();
        player.GetExperience(exp);
        player.BorrowGold(gold);
        cout << "경험치: +" << exp << ", 골드: +" << gold << endl;

        string dropName = monster.getItemDropName();
        Item* dropItem = ItemManager::Get().CreateItem(dropName);
        if (dropItem) {
            vector<Item*> dropItems = { dropItem };
            player.GetItem(dropItems);
            cout << "아이템 획득: " << dropItem->GetName() << endl;
        }
    }
    else {
        cout << player.GetName() << "이(가) 사망했습니다. 게임 오버." << endl;
    }
}