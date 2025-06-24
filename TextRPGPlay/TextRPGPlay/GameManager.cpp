#include "GameManager.h"
#include "Monster.h"
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
        cout << character->GetName() << "��(��) " << monster->getName()
            << "��(��) ����! ���� ü��: " << monster->getHealth() << endl;

        if (monster->IsAlive()) {
            int mDamage = monster->Attack();
            character->TakeDamage(mDamage);
            cout << monster->getName() << "�� �ݰ�! " << character->GetName()
                << " ü��: " << character->GetCurrentHealth() << endl;
        }
    }

    if (character->IsAlive()) {
        cout << "\n���� �¸�!" << endl;

        int exp = monster->getExpDrop();
        int gold = monster->getGoldDrop();
        character->GetExperience(exp);
        character->BorrowGold(gold);
        cout << "����ġ: +" << exp << ", ���: +" << gold << endl;

        ItemType dropType = monster->getItemDrop();
        string dropName = monster->getItemDropName();

        Item* dropItem = ItemManager::Get().CreateItem(dropName);
        if (dropItem) {
            vector<Item*> dropItems = { dropItem };
            character->GetItem(dropItems);
            cout << "������ ȹ��: " << dropItem->GetName() << endl;
        }
    }
    else {
        cout << character->GetName() << "��(��) ����߽��ϴ�. ���� ����." << endl;
    }

    delete monster;
}

void GameManager::DisplayInventory() {}

void GameManager::Run() {
    Character& player = *Character::Get();

    while (player.IsAlive() && player.GetLevel() < 10) {
        cout << "\n===== ĳ���� ���� =====" << endl;
        player.DisplayStatus();

        cout << "\n===== ���� ���� (����: " << player.GetLevel() << ") =====" << endl;
        Monster* monster = GenerateMonster(player.GetLevel());
        cout << monster->getName() << " ����! ü��: " << monster->getHealth()
            << ", ���ݷ�: " << monster->Attack() << endl;

        Battle(&player, monster);

        if (!player.IsAlive()) break;
    }

    if (player.IsAlive() && player.GetLevel() >= 10) {
        cout << "\n===== ���� ���� ���� =====" << endl;
        player.DisplayStatus();

        Monster* boss = GenerateBossMonster(player.GetLevel());
        cout << boss->getName() << " ����! ü��: " << boss->getHealth()
            << ", ���ݷ�: " << boss->Attack() << endl;

        Battle(&player, boss);
        delete boss;

        if (player.IsAlive()) {
            cout << "\n�����մϴ�! ������ ����ġ�� ������ Ŭ�����߽��ϴ�!" << endl;
        }
        else {
            cout << "\n�������� �й��߽��ϴ�. ���� ����." << endl;
        }
    }

    cout << "\n���� ����. �޸� ���� ��..." << endl;
    delete Character::Get();
}