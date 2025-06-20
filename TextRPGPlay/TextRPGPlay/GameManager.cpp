#include "GameManager.h"
#include "Goblin.h"
#include "Orc.h"
#include "Troll.h"
#include "Slime.h"
#include "Dragon.h"
#include "Character.h"
#include "Item.h"
#include "Inventory.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

GameManager::GameManager() {
    player = Character::GetInstance("���"); // �̱����� ���� ĳ���Ͱ�ü ����
}

Monster* GameManager::GenerateMonster(int level) {
    if (level <= 3) return new Slime(level);
    else if (level <= 5) return new Orc(level);
    else if (level <= 7) return new Troll(level);
    else return new Goblin(level);
}

BossMonster* GameManager::GenerateBossMonster(int level) {
    return new Dragon(level);
}

void GameManager::Battle(Character* character, Monster* monster) {
    while (character->isAlive() && monster->IsAlive()) {
        int damage = character->Attack();
        monster->takeDamage(damage);
        cout << character->GetName() << "��(��) " << monster->getName() << "��(��) ����! ���� ü��: " << monster->getHealth() << endl;

        if (monster->IsAlive()) {
            int mDamage = monster->Attack();
            character->TakeDamage(mDamage);
            cout << monster->getName() << "�� �ݰ�! " << character->GetName() << " ü��: " << character->GetCurrentHealth() << endl;
        }
    }

    if (character->isAlive()) {
        cout << "\n���� �¸�!" << endl;
        int exp = monster->getExpDrop();
        int gold = monster->getGoldDrop();
        character->GetExperience(exp);
        character->GainGold(gold);
        cout << "����ġ: +" << exp << ", ���: +" << gold << endl;

        string itemName = monster->getItemDrop();
        if (!itemName.empty()) {
            Item* dropItem = new Item(itemName);
            character->GetItem(dropItem, 1);
            cout << "������ ȹ��: " << dropItem->name << endl;
        }
    }
    else {
        cout << character->GetName() << "��(��) ����߽��ϴ�. ���� ����." << endl;
    }

    delete monster;
}

void GameManager::DisplayInventory(Character* character) {
    Inventory::GetInstance()->DisplayInventory();
}

void GameManager::Run() {
    while (player->isAlive() && player->GetLevel() < 10) {
        cout << "\n===== ���� ���� (����: " << player->GetLevel() << ") =====" << endl;
        Monster* monster = GenerateMonster(player->GetLevel());
        cout << monster->getName() << " ����! ü��: " << monster->getHealth() << ", ���ݷ�: " << monster->Attack() << endl;
        Battle(player, monster);

        if (!player->isAlive()) break;

        char choice;
        cout << "�κ��丮�� Ȯ���Ͻðڽ��ϱ�? (Y/N): ";
        cin >> choice;
        if (choice == 'Y' || choice == 'y') {
            DisplayInventory(player);
        }
    }

    if (player->isAlive() && player->GetLevel() >= 10) {
        cout << "\n===== ���� ���� ���� =====" << endl;
        BossMonster* boss = GenerateBossMonster(player->GetLevel());
        cout << boss->getName() << " ����! ü��: " << boss->getHealth() << ", ���ݷ�: " << boss->Attack() << endl;
        Battle(player, boss);
        delete boss;

        if (player->isAlive()) {
            cout << "\n�����մϴ�! ������ ����ġ�� ������ Ŭ�����߽��ϴ�!" << endl;
        }
        else {
            cout << "\n�������� �й��߽��ϴ�. ���� ����." << endl;
        }
    }

    cout << "\n���� ����. �޸� ���� ��..." << endl;
    Character::ReleaseInstance();
}