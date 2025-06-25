#include <iostream>
#include <string>

#include "Character.h"
#include "Inventory.h"
#include "GameManager.h"
#include "Item.h"
#include "Store.h"

using namespace std;

Inventory* Inventory::iveninstance = nullptr;

Inventory& Inventory::Get()
{
    if (iveninstance == nullptr)
    {
        iveninstance = new Inventory(); //�κ��丮 �������ֱ�
    }

    return *iveninstance;
}

#pragma region InventoryManagement
void Inventory::ClassificationItem(vector<Item*> items)
{
    for (Item* item : items) {
        bool hasItem = false;
        if (item->GetType() == ItemType::Expendables)
        {
            for (const unordered_map<Item*, int>::value_type& expen : expendableItems)
            {
                //������ ������ �ִ� �Һ������ �̶��
                if (expen.first->GetName() == item->GetName())
                {
                    expendableItems[expen.first] += 1; //������ �������ִ� ������ �߰����ֱ�
                    hasItem = true;
                    break;
                }
            }

            //�Һ��κ��丮�� �ش� �Һ�������� ���ٸ�
            if (!hasItem)
            {
                //���� �߰����ֱ�
                expendableItems[item] = 1;
            }
        }
        else if (item->GetType() == ItemType::Weapon)
        {
            weaponItems.push_back(item);
        }
        else if (item->GetType() == ItemType::Armor)
        {
            armorItems.push_back(item);
        }
        else if (item->GetType() == ItemType::Other)
        {
            for (const unordered_map<Item*, int>::value_type& other : otherItems)
            {
                //������ ������ �ִ� �Һ������ �̶��
                if (other.first->GetName() == item->GetName())
                {
                    otherItems[other.first] += 1; //������ �������ִ� ������ �߰����ֱ�
                    hasItem = true;
                    break;
                }
            }

            //�Һ��κ��丮�� �ش� �Һ�������� ���ٸ�
            if (!hasItem)
            {
                //���� �߰����ֱ�
                otherItems[item] = 1;
            }
        }
        cout << item->GetName() << "�� ȹ���߽��ϴ�." << endl;
    }
}

void Inventory::DisplayInventory(string func)
{
    int category;

    while (true) {
        cout << "Ȯ���� �κ��丮�� ī�װ� ��ȣ�� �Է����ּ���." << endl;
        cout << "1. �Ҹ��� ������" << endl;
        cout << "2. ����" << endl;
        cout << "3. ��" << endl;
        cout << "4. ��Ÿ ������" << endl;
        cout << "0. ����" << endl;
        cout << "�Է�: ";
        cin >> category;

        switch (category)
        {
            case 0: return;
            case 1: DisplayExpendableItem(func); break;
            case 2: DisplayWeapon(func); break;
            case 3: DisplayArmor(func); break;
            case 4: DIsplayOtherItem(func); break;
            default: cout << GameManager::Get().WrongInputMessage(); break;
        }
    }
}

void Inventory::DisplayWeapon(string func)
{
    //�����ϰ� �ִ� ���Ⱑ ���� ��
    if (weaponItems.empty())
    {
        cout << "�����ϰ� �ִ� ���Ⱑ �����ϴ�." << endl;
        DisplayInventory(func);
        return;
    }

    cout << "���� ���" << endl;
    for (int i = 0; i < weaponItems.size(); i++)
    {
        cout << i + 1 << "." << weaponItems[i]->GetName() << endl;
    }

    int num = 0;
    while (true)
    {
        if (func == use)
        {
            cout << "������ ������ ��ȣ�� �Է��� �ּ���(����ϱ� '0' �Է�): ";
        }
        else if (func == sell)
        {
            cout << "�Ǹ��� ������ ��ȣ�� �Է��� �ּ���(����ϱ� '0' �Է�): ";
        }
        else
        {
            cout << "���� �۾� �����ϱ�" << endl;
            DisplayInventory(func);
            return;
        }
        cin >> num;

        if (num == 0)
        {
            cout << "����߽��ϴ�." << endl;
            DisplayInventory(func);
            return;
        }
        //��� ������ ��
        else if (num > 0 && num <= weaponItems.size())
        {
            if (func == use)
            {
                weaponItems[num - 1]->Use(this);
            }
            else if (func == sell)
            {
                Store::Get().SellItem(weaponItems[num - 1]);//�Ǹ�
            }
            DisplayWeapon(func);
        }
        else
        {
            cout << GameManager::Get().WrongInputMessage();
        }
    }
}

void Inventory::DisplayArmor(string func)
{
    //�����ϰ� �ִ� ���� ���� ��
    if (armorItems.empty()) {
        cout << "�����ϰ� �ִ� ���� �����ϴ�." << endl;
        DisplayInventory(func);
        return;
    }

    cout << "�� ���" << endl;
    for (int i = 0; i < armorItems.size(); i++) {
        cout << i + 1 << ".: " << armorItems[i]->GetName() << endl;
    }

    int num = 0;
    while (true)
    {
        if (func == use)
        {
            cout << "������ ���� ��ȣ�� �Է��� �ּ���(����ϱ� '0' �Է�): ";
        }
        else if (func == sell)
        {
            cout << "�Ǹ��� ���� ��ȣ�� �Է��� �ּ���(����ϱ� '0' �Է�): ";
        }
        else
        {
            cout << "���� �۾� �����ϱ�" << endl;
            DisplayInventory(func);
            return;
        }
        cin >> num;

        if (num == 0)
        {
            cout << "����߽��ϴ�." << endl;
            DisplayInventory(func);
            return;
        }
        //��� ������ ��
        else if (num > 0 && num <= armorItems.size())
        {
            if (func == use)
            {
                armorItems[num - 1]->Use(this);
            }
            else if (func == sell)
            {
                Store::Get().SellItem(armorItems[num - 1]);//�Ǹ�
            }
            DisplayArmor(func);
            return;
        }
        else
        {
            cout << GameManager::Get().WrongInputMessage();
        }
    }
}

void Inventory::DisplayExpendableItem(string func)
{
    //�����ϰ� �ִ� �Һ�������� ���� ��
    if (expendableItems.empty())
    {
        cout << "�����ϰ� �ִ� �Һ������ �����ϴ�." << endl;
        DisplayInventory(func);
        return;
    }

    cout << "�Һ� ������ ���" << endl;
    int num = 0;
    for (unordered_map<Item*, int>::value_type& p : expendableItems)
    {
        ++num;
        cout << num << "." << p.first->GetName() << "" << p.second << "��" << endl;
    }

    string key;
    while (true)
    {
        if (func == use)
        {
            cout << "����� �������� �̸��� �Է��� �ּ���(����ϱ� 'p' �Է�): ";
        }
        else if (func == sell)
        {
            cout << "�Ǹ��� �������� �̸��� �Է��� �ּ���(����ϱ� 'p' �Է�): ";
        }
        else
        {
            cout << "���� �۾� �����ϱ�" << endl;
            DisplayInventory(func);
            return;
        }

        cin >> key;
        if (key == "p")
        {
            cout << "����߽��ϴ�." << endl;
            DisplayInventory(func);
            return;
        }
        for (unordered_map<Item*, int>::value_type& item : expendableItems)
        {
            if (item.first->GetName() == key) {
                if (func == use)
                {
                    item.first->Use(&Character::Get());
                }
                else if (func == sell)
                {
                    Store::Get().SellItem(item.first);//�Ǹŷ���
                }
                DisplayExpendableItem(func);
                return;
            }
            //ã�ƺ��� �����ϰ� ���� �ʴ� ������ �̸��� ��
            if (key != item.first->GetName() && expendableItems.find(item.first) == expendableItems.end())
            {
                cout << GameManager::Get().WrongInputMessage();
                DisplayExpendableItem(func);
                return;
            }
        }
    }
}
void Inventory::DIsplayOtherItem(string func)
{
    //�����ϰ� �ִ� ��Ÿ�������� ���� ��
    if (otherItems.empty())
    {
        cout << "�����ϰ� �ִ� ��Ÿ������ �����ϴ�." << endl;
        DisplayInventory(func);
        return;
    }

    cout << "��Ÿ ������ ���" << endl;
    int num = 0;
    for (unordered_map<Item*, int>::value_type& p : otherItems)
    {
        ++num;
        cout << num << "." << p.first->GetName() << ": " << p.second << "��" << endl;
    }

    string key;
    while (true)
    {
        if (func == sell)
        {
            cout << "�Ǹ��� �������� �̸��� �Է��� �ּ���(����ϱ� 'p' �Է�): ";
        }
        else
        {
            cout << "���� �۾� �����ϱ�" << endl;
            DisplayInventory(func);
            return;
        }

        cin.ignore();
        getline(cin, key);
        if (key == "p")
        {
            cout << "����߽��ϴ�." << endl;
            DisplayInventory(func);
            return;
        }
        for (unordered_map<Item*, int>::value_type& item : otherItems)
        {
            if (item.first->GetName() == key) {
                if (func == sell)
                {
                    Store::Get().SellItem(item.first);//�Ǹ�
                    DIsplayOtherItem(func);
                    return;
                }
            }
            //ã�ƺ��� �����ϰ� ���� �ʴ� ������ �̸��� ��
            else if (otherItems.begin() == prev(otherItems.end()) && key != item.first->GetName())
            {
                cout << GameManager::Get().WrongInputMessage();
                DIsplayOtherItem(func);
                return;
            }
        }
    }
}

void Inventory::RemoveEquipItem(Item* equip)
{
    if (equip->GetType() == ItemType::Weapon)
    {
        vector<Item*>::iterator item = find(weaponItems.begin(), weaponItems.end(), equip);
        weaponItems.erase(item);
    }
    else if (equip->GetType() == ItemType::Armor)
    {
        vector<Item*>::iterator item = find(armorItems.begin(), armorItems.end(), equip);
        armorItems.erase(item);
    }
}
void Inventory::RemoveNoneEquipItem(const unordered_map<string, int>& materials, ItemType type)
{
    unordered_map<Item*, int>& inventory = (type == ItemType::Expendables) ? expendableItems : otherItems;

    for (const unordered_map<string, int>::value_type& material : materials)
    {
        const string& itemName = material.first;
        int amountToRemove = material.second;

        for (unordered_map<Item*, int>::value_type& other : inventory)
        {
            if (other.first->GetName() == itemName)
            {
                if (other.second > amountToRemove)
                {
                    other.second -= amountToRemove;
                }
                else if (other.second == amountToRemove)
                {
                    otherItems.erase(other.first);
                }
                break;
            }
        }
    }
}
#pragma endregion

#pragma region EquipManagement
void Inventory::EquipWeapon(Item* weapon)
{
    //�̹� �������� ��
    if (weapon->GetEquip())
    {
        cout << "�̹� �������� �����Դϴ�." << endl;
        return;
    }
    //�������� �ƴ� ��
    else
    {
        //������ ������ ���Ⱑ ������
        if (Character::Get().GetEquipWeapon() != nullptr)
        {
            //��������
            UnEquipWeapon();
        }
        //���ο� ���� ����
        Character::Get().SetEquipWeapon(weapon);
        weapon->SetEquip(true); //�ش� ���� �������·� ����
        Character::Get().UpadatePlayerStatus(); //�÷��̾� ���� ������Ʈ
    }
    DisplayWeapon(use); //���� �۾����� �ǵ��ư���
}
void Inventory::EquipArmor(Item* armor)
{
    //�̹� �������� ��
    if (armor->GetEquip())
    {
        cout << "�̹� �������� ���Դϴ�." << endl;
        return;
    }
    else
    {
        //������ ������ ���� ������
        if (Character::Get().GetEquipArmor() != nullptr)
        {
            //���� �� ����
            UnEquipArmor();
        }

        //���ο� �� ����
        Character::Get().SetEquipArmor(armor);
        armor->SetEquip(true); //�ش� �� ���� ���·� ����
        Character::Get().UpadatePlayerStatus(); //�÷��̾� ���� ������Ʈ
    }
    DisplayArmor(use); //���� �۾����� �ǵ��ư���
}
void Inventory::UnEquipWeapon()
{
    Character::Get().GetEquipWeapon()->SetEquip(false);
}
void Inventory::UnEquipArmor()
{
    Character::Get().GetEquipArmor()->SetEquip(false);
}
#pragma endregion

Inventory::~Inventory()
{
    for (unordered_map<Item*, int>::value_type& it : expendableItems) {
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