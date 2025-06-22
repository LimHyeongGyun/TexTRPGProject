#include <iostream>
#include "Character.h"
#include "Inventory.h"
#include "Item.h"

using namespace std;

Inventory* Inventory::iveninstance = nullptr;

Inventory* Inventory::Get()
{
    if (iveninstance == nullptr)
    {
        iveninstance = new Inventory(); //�κ��丮 �������ֱ�
    }

    return iveninstance;
}

void Inventory::ClassificationItem(vector<Item*> items)
{
    for (Item* item : items) {
        if (item->itemType == Expendable)
        {
            //�Һ��κ��丮�� �ش� �Һ�������� ���ٸ�
            if (expendableItems.find(item) == expendableItems.end()) {
                expendableItems[item] = 1;
            }
            //������ ������ �ִ� �Һ������ �̶��
            else if (expendableItems.find(item) != expendableItems.end()) {
                expendableItems[item] += 1; //������ �������ִ� ������ �߰����ֱ�
            }
        }
        else if (item->itemType == Weapon)
        {
            weaponItems.push_back(item);
        }
        else if (item->itemType == Armor)
        {
            armorItems.push_back(item);
        }
        else if (item->itemType == Other)
        {
            otherItems.push_back(item);
        }
    }
}

void Inventory::DisplayInventory()
{
    int category;

    while (true) {
        cout << "Ȯ���� �κ��丮�� ī�װ� ��ȣ�� �Է����ּ���." << endl;
        cout << "1. �Ҹ��� ������" << endl;
        cout << "2. ����" << endl;
        cout << "3. ��" << endl;
        cout << "0. ����" << endl;
        cout << "�Է�: ";
        cin >> category;

        switch (category)
        {
            case 0: return;
            case 1: DisplayConsumeItem(); break;
            case 2: DisplayWeapon(); break;
            case 3: DisplayArmor(); break;
            default: cout << "��ȿ���� ���� �Է��Դϴ�" << endl; break;
        }
    }
}

void Inventory::DisplayConsumeItem()
{
    //�����ϰ� �ִ� �Һ�������� ���� ��
    if (expendableItems.empty())
    {
        cout << "�����ϰ� �ִ� �Һ������ �����ϴ�." << endl;
        return;
    }

    cout << "�Һ� ������ ���" << endl;
    for (unordered_map<Item*, int>::value_type& p : expendableItems)
    {
        cout << "������ �̸�" << p.first->name << "" << p.second << "��" << endl;
    }

    string key;
    cout << "����� �������� �̸��� �Է��� �ּ���: (����ϱ� 'p' �Է�)" << key << endl;
    if (key == "p")
    {
        cout << "����߽��ϴ�." << endl;
        return;
    }

    Character* character = Character::Get();
    for (unordered_map<Item*, int>::value_type& item : expendableItems)
    {
        if (item.first->name == key) {
            item.first->Use(character);
            return;
        }
    }

    cout << "�Է��� �̸��� �������� �����ϴ�." << endl;
}

void Inventory::DisplayWeapon()
{
    //�����ϰ� �ִ� ���Ⱑ ���� ��
    if (weaponItems.empty())
    {
        cout << "�����ϰ� �ִ� ���Ⱑ �����ϴ�." << endl;
        return;
    }

    cout << "���� ���" << endl;
    for (int i = 0; i < weaponItems.size(); i++)
    {
        cout << i + 1 << "." << weaponItems[i]->name << endl;
    }

    int num = 0;
    cout << "������ ������ ��ȣ�� �Է��� �ּ���(����ϱ� '0' �Է�): ";
    cin >> num;

    if (num == 0)
    {
        cout << "����߽��ϴ�." << endl;
        return;
    }
    //��� ������ ��
    if (num > 0 && num <= weaponItems.size()) {
        weaponItems[num - 1]->Use(Character::Get(), this);
    }
    else
    {
        cout << "��ȿ���� ���� ��ȣ�Դϴ�." << endl;
    }
}

void Inventory::DisplayArmor()
{
    //�����ϰ� �ִ� ���� ���� ��
    if (armorItems.empty()) {
        cout << "�����ϰ� �ִ� ���� �����ϴ�." << endl;
        return;
    }

    cout << "�� ���" << endl;
    for (int i = 0; i < armorItems.size(); i++) {
        cout << i + 1 << ".: " << armorItems[i]->name << endl;
    }

    int num = 0;
    cout << "������ ���� ��ȣ�� �Է��� �ּ���(����ϱ� '0' �Է�): " << num << endl;

    if (num == 0)
    {
        cout << "����߽��ϴ�." << endl;
        return;
    }

    //��� ������ ��
    if (num > 0 && num <= armorItems.size()) {
        armorItems[num - 1]->Use(Character::Get(), this);
    }
    else
    {
        cout << "��ȿ���� ���� ��ȣ�Դϴ�." << endl;
    }
}


void Inventory::EquipWeapon(Item* weapon)
{
    weapon->SetEquipped(true);

    Character* character = Character::Get();
    Item* equipped = character->GetEquipWeapon();

    //������ ���Ⱑ ������
    if (equipped != nullptr)
    {
        //��������
        UnEquipWeapon();
        character->UnEquipStatus(equipped->attack, 0); //���� ���� �ɷ�ġ ����
    }

    character->SetEquipWeapon(weapon);
    character->EquipStatus(weapon->attack, 0);
}
void Inventory::EquipArmor(Item* armor)
{
    armor->SetEquipped(true);

    Character* character = Character::Get();
    Item* equipped = character->GetEquipArmor();

    //������ ���� ������
    if (equipped != nullptr)
    {
        //���� �� ����
        UnEquipArmor();
        character->UnEquipStatus(0, equipped->health); //���� ���� �ɷ�ġ ����
    }
    //���ο� �� ����
    character->SetEquipArmor(armor);
    character->EquipStatus(0, armor->health);
}
void Inventory::UnEquipWeapon()
{
    Character::Get()->GetEquipWeapon()->SetEquipped(false);
}
void Inventory::UnEquipArmor()
{
    Character::Get()->GetEquipArmor()->SetEquipped(false);
}

Inventory::~Inventory()
{
    for (auto& it : expendableItems) {
        delete it.first;
    }

    for (Item* weapon : weaponItems)
    {
        delete weapon;
    }
    for (Item* armor : armorItems)
    {
        delete armor;
    }

    delete iveninstance;
    iveninstance = nullptr;
}