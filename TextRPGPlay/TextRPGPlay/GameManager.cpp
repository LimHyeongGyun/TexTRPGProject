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
        cout << "\n===== ĳ���� ���� =====" << endl;
        player.DisplayStatus();

        cout << "\n===== ���� ���� (����: " << player.GetLevel() << ") =====" << endl;

        int level = player.GetLevel();
        Monster monster;
        if (level <= 3) monster = GenerateSlime(level);
        else if (level <= 5) monster = GenerateOrc(level);
        else if (level <= 7) monster = GenerateTroll(level);
        else monster = GenerateGoblin(level);

        cout << monster.getName() << " ����! ü��: " << monster.getHealth()
            << ", ���ݷ�: " << monster.Attack() << endl;

        Battle(player, monster);

        if (!player.IsAlive()) break;
    }

    if (player.IsAlive() && player.GetLevel() >= 10) {
        cout << "\n===== ���� ���� ���� =====" << endl;
        player.DisplayStatus();

        Monster boss = GenerateDragon(player.GetLevel());

        cout << boss.getName() << " ����! ü��: " << boss.getHealth()
            << ", ���ݷ�: " << boss.Attack() << endl;

        Battle(player, boss);

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

void GameManager::Battle(Character& player, Monster& monster) {
    while (player.IsAlive() && monster.IsAlive()) {
        int damage = player.Attack();
        monster.takeDamage(damage);
        cout << player.GetName() << "��(��) " << monster.getName()
            << "��(��) ����! ���� ü��: " << monster.getHealth() << endl;

        if (monster.IsAlive()) {
            int mDamage = monster.Attack();
            player.TakeDamage(mDamage);
            cout << monster.getName() << "�� �ݰ�! " << player.GetName()
                << " ü��: " << player.GetCurrentHealth() << endl;
        }
    }

    if (player.IsAlive()) {
        cout << "\n���� �¸�!" << endl;

        int exp = monster.getExpDrop();
        int gold = monster.getGoldDrop();
        player.GetExperience(exp);
        player.BorrowGold(gold);
        cout << "����ġ: +" << exp << ", ���: +" << gold << endl;

        string dropName = monster.getItemDropName();
        Item* dropItem = ItemManager::Get().CreateItem(dropName);
        if (dropItem) {
            vector<Item*> dropItems = { dropItem };
            player.GetItem(dropItems);
            cout << "������ ȹ��: " << dropItem->GetName() << endl;
        }
    }
    else {
        cout << player.GetName() << "��(��) ����߽��ϴ�. ���� ����." << endl;
    }
}