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
        cout << "\n===== ĳ���� ���� =====" << endl;
        player.DisplayStatus();

        cout << "\n===== ���� ���� (����: " << player.GetLevel() << ") =====" << endl;

        int level = player.GetLevel();
        Monster* monster = nullptr;

        if (level <= 3) monster = GenerateSlime(level);
        else if (level <= 5) monster = GenerateOrc(level);
        else if (level <= 7) monster = GenerateTroll(level);
        else monster = GenerateGoblin(level);

        cout << monster->getName() << " ����! ü��: " << monster->getHealth()
            << ", ���ݷ�: " << monster->Attack() << endl;

        Battle(&player, monster);
        delete monster;

        if (player.GetHealth() <= 0) break;
    }

    if (player.GetHealth() > 0 && player.GetLevel() >= 10) {
        cout << "\n===== ���� ���� ���� =====" << endl;
        player.DisplayStatus();

        Monster* boss = GenerateDragon(player.GetLevel());

        cout << boss->getName() << " ����! ü��: " << boss->getHealth()
            << ", ���ݷ�: " << boss->Attack() << endl;

        Battle(&player, boss);
        delete boss;

        if (player.GetHealth() > 0) {
            cout << "\n�����մϴ�! ������ ����ġ�� ������ Ŭ�����߽��ϴ�!" << endl;
        }
        else {
            cout << "\n�������� �й��߽��ϴ�. ���� ����." << endl;
        }
    }

    cout << "\n���� ����. �޸� ���� ��..." << endl;
}

void GameManager::Battle(Character* player, Monster* monster) {
    while (player->GetHealth() > 0 && monster->getHealth() > 0) {
        cout << "\n==== �ൿ�� �����ϼ��� ====\n";
        cout << "1. ����\n";
        cout << "2. ������ ���\n";
        cout << "3. ��������\n";
        cout << "�Է� >> ";

        int choice;
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "�߸��� �Է��Դϴ�.\n";
            continue;
        }

        if (choice == 1) {
            int damage = player->Attack();
            monster->takeDamage(damage);
            cout << player->GetName() << "��(��) " << monster->getName()
                << "��(��) ����! ���� ü��: " << monster->getHealth() << endl;
        }
        else if (choice == 2) {
            Inventory::Get().DisplayConsumeItem();
            cout << "����� ������ ��ȣ �Է� >> ";
            int index;
            cin >> index;
            player->UseItem(index);
            continue;
        }
        else if (choice == 3) {
            cout << "�����ƽ��ϴ�!\n";
            return;
        }
        else {
            cout << "�߸��� �����Դϴ�. �ٽ� �Է��ϼ���.\n";
            continue;
        }

        if (monster->getHealth() > 0) {
            int mDamage = monster->Attack();
            player->TakeDamage(mDamage);
            cout << monster->getName() << "�� �ݰ�! " << player->GetName()
                << " ü��: " << player->GetHealth() << endl;
        }
    }

    if (player->GetHealth() > 0) {
        cout << "\n���� �¸�!" << endl;

        int exp = monster->getExpDrop();
        int gold = monster->getGoldDrop();
        player->GetExperience(exp);
        player->BorrowGold(gold);
        cout << "����ġ: +" << exp << ", ���: +" << gold << endl;

        Item* dropItem = monster->ItemDrop();
        if (dropItem) {
            vector<Item*> dropItems = { dropItem };
            player->GetItem(dropItems);
            cout << "������ ȹ��: " << dropItem->GetName() << endl;
        }
    }
    else {
        cout << player->GetName() << "��(��) ����߽��ϴ�. ���� ����." << endl;
    }
}