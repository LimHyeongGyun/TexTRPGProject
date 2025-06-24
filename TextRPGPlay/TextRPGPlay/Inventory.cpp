#include <iostream>
#include <string>

#include "Character.h"
#include "Inventory.h"
#include "Item.h"

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

void Inventory::DisplayInventory()
{
    int category;

    while (true) {
        cout << "확인할 인벤토리의 카테고리 번호를 입력해주세요." << endl;
        cout << "1. 소모형 아이템" << endl;
        cout << "2. 무기" << endl;
        cout << "3. 방어구" << endl;
        cout << "0. 종료" << endl;
        cout << "입력: ";
        cin >> category;

        switch (category)
        {
            case 0: return;
            case 1: DisplayConsumeItem(); break;
            case 2: DisplayWeapon(); break;
            case 3: DisplayArmor(); break;
            default: cout << "유효하지 않은 입력입니다" << endl; break;
        }
    }
}

void Inventory::DisplayConsumeItem()
{
    //소지하고 있는 소비아이템이 없을 때
    if (expendableItems.empty())
    {
        cout << "소지하고 있는 소비아이템 없습니다." << endl;
        return;
    }

    cout << "소비 아이템 목록" << endl;
    for (unordered_map<Item*, int>::value_type& p : expendableItems)
    {
        cout << "아이템 이름" << p.first->GetName() << "" << p.second << "개" << endl;
    }

    string key;
    cout << "사용할 아이템의 이름을 입력해 주세요: (취소하기 'p' 입력)" << key << endl;
    if (key == "p")
    {
        cout << "취소했습니다." << endl;
        return;
    }

    Character& character = Character::Get();
    for (unordered_map<Item*, int>::value_type& item : expendableItems)
    {
        if (item.first->GetName() == key) {
            item.first->Use(&character);
            return;
        }
    }

    cout << "입력한 이름의 아이템이 없습니다." << endl;
}

void Inventory::DisplayWeapon()
{
    //소지하고 있는 무기가 없을 때
    if (weaponItems.empty())
    {
        cout << "소지하고 있는 무기가 없습니다." << endl;
        return;
    }

    cout << "무기 목록" << endl;
    for (int i = 0; i < weaponItems.size(); i++)
    {
        cout << i + 1 << "." << weaponItems[i]->GetName() << endl;
    }

    int num = 0;
    cout << "장착할 무기의 번호를 입력해 주세요(취소하기 '0' 입력): ";
    cin >> num;

    if (num == 0)
    {
        cout << "취소했습니다." << endl;
        return;
    }
    //장비를 장착할 때
    if (num > 0 && num <= weaponItems.size()) {
        weaponItems[num - 1]->Use(this);
    }
    else
    {
        cout << "유효하지 않은 번호입니다." << endl;
    }
}

void Inventory::DisplayArmor()
{
    //소지하고 있는 방어구가 없을 때
    if (armorItems.empty()) {
        cout << "소지하고 있는 방어구가 없습니다." << endl;
        return;
    }

    cout << "방어구 목록" << endl;
    for (int i = 0; i < armorItems.size(); i++) {
        cout << i + 1 << ".: " << armorItems[i]->GetName() << endl;
    }

    int num = 0;
    cout << "장착할 방어구의 번호를 입력해 주세요(취소하기 '0' 입력): " << num << endl;

    if (num == 0)
    {
        cout << "취소했습니다." << endl;
        return;
    }

    //장비를 장착할 때
    if (num > 0 && num <= armorItems.size()) {
        armorItems[num - 1]->Use(this);
    }
    else
    {
        cout << "유효하지 않은 번호입니다." << endl;
    }
}

void Inventory::EquipWeapon(Item* weapon)
{
    //이미 착용중일 때
    if (weapon->GetEquip())
    {
        cout << "이미 착용중인 무기입니다." << endl;
    }
    //착용중이 아닐 때
    else
    {
        weapon->SetEquip(true);

        Character& character = Character::Get();
        Item* equipped = character.GetEquipWeapon();

        //장착한 무기가 있을때
        if (equipped != nullptr)
        {
            //무기해제
            UnEquipWeapon();
            character.UnEquipStatus(equipped->GetAtack(), 0); //장비로 얻은 능력치 해제
        }

        character.SetEquipWeapon(weapon);
        character.EquipStatus(weapon->GetAtack(), 0);
    }
}
void Inventory::EquipArmor(Item* armor)
{
    //이미 착용중일 때
    if (armor->GetEquip())
    {
        cout << "이미 착용중인 방어구입니다." << endl;
    }
    else
    {
        armor->SetEquip(true);

        Character& character = Character::Get();
        Item* equipped = character.GetEquipArmor();

        //장착한 방어구가 있을때
        if (equipped != nullptr)
        {
            //기존 방어구 해제
            UnEquipArmor();
            character.UnEquipStatus(0, equipped->GetBonusHealth()); //장비로 얻은 능력치 해제
        }
        //새로운 방어구 장착
        character.SetEquipArmor(armor);
        character.EquipStatus(0, armor->GetBonusHealth());
    }
}
void Inventory::UnEquipWeapon()
{
    Character::Get().GetEquipWeapon()->SetEquip(false);
}
void Inventory::UnEquipArmor()
{
    Character::Get().GetEquipArmor()->SetEquip(false);
}

void Inventory::RemoveItem(const unordered_map<string, int>& materials)
{
    for (const unordered_map<string, int>::value_type& material : materials)
    {
        const string& itemName = material.first;
        int amountToRemove = material.second;

        for (unordered_map<Item*, int>::value_type& other : otherItems)
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