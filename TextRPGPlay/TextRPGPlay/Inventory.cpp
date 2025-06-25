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
        iveninstance = new Inventory(); //인벤토리 생성해주기
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
                //기존에 가지고 있던 소비아이템 이라면
                if (expen.first->GetName() == item->GetName())
                {
                    expendableItems[expen.first] += 1; //기존에 가지고있던 갯수에 추가해주기
                    hasItem = true;
                    break;
                }
            }

            //소비인벤토리에 해당 소비아이템이 없다면
            if (!hasItem)
            {
                //새로 추가해주기
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
                //기존에 가지고 있던 소비아이템 이라면
                if (other.first->GetName() == item->GetName())
                {
                    otherItems[other.first] += 1; //기존에 가지고있던 갯수에 추가해주기
                    hasItem = true;
                    break;
                }
            }

            //소비인벤토리에 해당 소비아이템이 없다면
            if (!hasItem)
            {
                //새로 추가해주기
                otherItems[item] = 1;
            }
        }
        cout << item->GetName() << "을 획득했습니다." << endl;
    }
}

void Inventory::DisplayInventory(string func)
{
    int category;

    while (true) {
        cout << "확인할 인벤토리의 카테고리 번호를 입력해주세요." << endl;
        cout << "1. 소모형 아이템" << endl;
        cout << "2. 무기" << endl;
        cout << "3. 방어구" << endl;
        cout << "4. 기타 아이템" << endl;
        cout << "0. 종료" << endl;
        cout << "입력: ";
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
    //소지하고 있는 무기가 없을 때
    if (weaponItems.empty())
    {
        cout << "소지하고 있는 무기가 없습니다." << endl;
        DisplayInventory(func);
        return;
    }

    cout << "무기 목록" << endl;
    for (int i = 0; i < weaponItems.size(); i++)
    {
        cout << i + 1 << "." << weaponItems[i]->GetName() << endl;
    }

    int num = 0;
    while (true)
    {
        if (func == use)
        {
            cout << "장착할 무기의 번호를 입력해 주세요(취소하기 '0' 입력): ";
        }
        else if (func == sell)
        {
            cout << "판매할 무기의 번호를 입력해 주세요(취소하기 '0' 입력): ";
        }
        else
        {
            cout << "현재 작업 종료하기" << endl;
            DisplayInventory(func);
            return;
        }
        cin >> num;

        if (num == 0)
        {
            cout << "취소했습니다." << endl;
            DisplayInventory(func);
            return;
        }
        //장비를 장착할 때
        else if (num > 0 && num <= weaponItems.size())
        {
            if (func == use)
            {
                weaponItems[num - 1]->Use(this);
            }
            else if (func == sell)
            {
                Store::Get().SellItem(weaponItems[num - 1]);//판매
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
    //소지하고 있는 방어구가 없을 때
    if (armorItems.empty()) {
        cout << "소지하고 있는 방어구가 없습니다." << endl;
        DisplayInventory(func);
        return;
    }

    cout << "방어구 목록" << endl;
    for (int i = 0; i < armorItems.size(); i++) {
        cout << i + 1 << ".: " << armorItems[i]->GetName() << endl;
    }

    int num = 0;
    while (true)
    {
        if (func == use)
        {
            cout << "장착할 방어구의 번호를 입력해 주세요(취소하기 '0' 입력): ";
        }
        else if (func == sell)
        {
            cout << "판매할 방어구의 번호를 입력해 주세요(취소하기 '0' 입력): ";
        }
        else
        {
            cout << "현재 작업 종료하기" << endl;
            DisplayInventory(func);
            return;
        }
        cin >> num;

        if (num == 0)
        {
            cout << "취소했습니다." << endl;
            DisplayInventory(func);
            return;
        }
        //장비를 장착할 때
        else if (num > 0 && num <= armorItems.size())
        {
            if (func == use)
            {
                armorItems[num - 1]->Use(this);
            }
            else if (func == sell)
            {
                Store::Get().SellItem(armorItems[num - 1]);//판매
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
    //소지하고 있는 소비아이템이 없을 때
    if (expendableItems.empty())
    {
        cout << "소지하고 있는 소비아이템 없습니다." << endl;
        DisplayInventory(func);
        return;
    }

    cout << "소비 아이템 목록" << endl;
    int num = 0;
    for (unordered_map<Item*, int>::value_type& p : expendableItems)
    {
        ++num;
        cout << num << "." << p.first->GetName() << "" << p.second << "개" << endl;
    }

    string key;
    while (true)
    {
        if (func == use)
        {
            cout << "사용할 아이템의 이름을 입력해 주세요(취소하기 'p' 입력): ";
        }
        else if (func == sell)
        {
            cout << "판매할 아이템의 이름을 입력해 주세요(취소하기 'p' 입력): ";
        }
        else
        {
            cout << "현재 작업 종료하기" << endl;
            DisplayInventory(func);
            return;
        }

        cin >> key;
        if (key == "p")
        {
            cout << "취소했습니다." << endl;
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
                    Store::Get().SellItem(item.first);//판매로직
                }
                DisplayExpendableItem(func);
                return;
            }
            //찾아봐도 소지하고 있지 않는 아이템 이름일 때
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
    //소지하고 있는 기타아이템이 없을 때
    if (otherItems.empty())
    {
        cout << "소지하고 있는 기타아이템 없습니다." << endl;
        DisplayInventory(func);
        return;
    }

    cout << "기타 아이템 목록" << endl;
    int num = 0;
    for (unordered_map<Item*, int>::value_type& p : otherItems)
    {
        ++num;
        cout << num << "." << p.first->GetName() << ": " << p.second << "개" << endl;
    }

    string key;
    while (true)
    {
        if (func == sell)
        {
            cout << "판매할 아이템의 이름을 입력해 주세요(취소하기 'p' 입력): ";
        }
        else
        {
            cout << "현재 작업 종료하기" << endl;
            DisplayInventory(func);
            return;
        }

        cin.ignore();
        getline(cin, key);
        if (key == "p")
        {
            cout << "취소했습니다." << endl;
            DisplayInventory(func);
            return;
        }
        for (unordered_map<Item*, int>::value_type& item : otherItems)
        {
            if (item.first->GetName() == key) {
                if (func == sell)
                {
                    Store::Get().SellItem(item.first);//판매
                    DIsplayOtherItem(func);
                    return;
                }
            }
            //찾아봐도 소지하고 있지 않는 아이템 이름일 때
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
    //이미 착용중일 때
    if (weapon->GetEquip())
    {
        cout << "이미 착용중인 무기입니다." << endl;
        return;
    }
    //착용중이 아닐 때
    else
    {
        //기존에 장착한 무기가 있을때
        if (Character::Get().GetEquipWeapon() != nullptr)
        {
            //무기해제
            UnEquipWeapon();
        }
        //새로운 무기 장착
        Character::Get().SetEquipWeapon(weapon);
        weapon->SetEquip(true); //해당 무기 장착상태로 변경
        Character::Get().UpadatePlayerStatus(); //플레이어 스탯 업데이트
    }
    DisplayWeapon(use); //이전 작업으로 되돌아가기
}
void Inventory::EquipArmor(Item* armor)
{
    //이미 착용중일 때
    if (armor->GetEquip())
    {
        cout << "이미 착용중인 방어구입니다." << endl;
        return;
    }
    else
    {
        //기존에 장착한 방어구가 있을때
        if (Character::Get().GetEquipArmor() != nullptr)
        {
            //기존 방어구 해제
            UnEquipArmor();
        }

        //새로운 방어구 장착
        Character::Get().SetEquipArmor(armor);
        armor->SetEquip(true); //해당 방어구 장착 상태로 변경
        Character::Get().UpadatePlayerStatus(); //플레이어 스탯 업데이트
    }
    DisplayArmor(use); //이전 작업으로 되돌아가기
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