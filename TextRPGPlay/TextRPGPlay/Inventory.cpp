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
        iveninstance = new Inventory(); //인벤토리 생성해주기
    }

    return iveninstance;
}

void Inventory::ClassificationItem(vector<Item*> items)
{
    for (Item* item : items) {
        if (item->itemType == Consumable)
        {
            //소비인벤토리에 해당 소비아이템이 없다면
            if (consumableValue.find(item) == consumableValue.end()) {
                consumableValue[item] = 1;
            }
            //기존에 가지고 있던 소비아이템 이라면
            else if (consumableValue.find(item) != consumableValue.end()) {
                consumableValue[item] += 1; //기존에 가지고있던 갯수에 추가해주기
            }
        }
        else if (item->itemType == Weapon)
        {
            weaponValue.push_back(item);
        }
        else if (item->itemType == Armor)
        {
            armorValue.push_back(item);
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

    cout << "확인할 인벤토리의 카테고리 번호를 입력해주세요." << endl;
    cout << "1. 소모형 아이템" << endl;
    cout << "2. 무기" << endl;
    cout << "3. 방어구" << endl;
    cin >> category;

    if (category == 1)
    {
        DisplayConsumeItem();
    }
    else if (category == 2)
    {
        DisplayWeapon();
    }
    else if (category == 3)
    {
        DisplayArmor();
    }
}

void Inventory::DisplayConsumeItem()
{
    //소지하고 있는 소비아이템이 없을 때
    if (consumableValue.empty())
    {
        cout << "소지하고 있는 소비아이템 없습니다." << endl;
        return;
    }

    for (unordered_map<Item*, int>::value_type& p : consumableValue)
    {
        cout << "아이템 이름" << p.first->name << "" << p.second << "개" << endl;
    }

    string key;
    cout << "사용할 아이템의 이름을 입력해 주세요: (취소하기 'p' 입력)" << key << endl;
    if (key == "p")
    {
        cout << "취소했습니다." << endl;
    }
    else if (key != "p")
    {
        Character* character = Character::Get();
        for (unordered_map<Item*, int>::value_type& p : consumableValue)
        {
            if (p.first->name == key) {
                p.first->Use(character);
            }
        }
    }
}

void Inventory::DisplayWeapon()
{
    //소지하고 있는 무기가 없을 때
    if (weaponValue.size() == 0) {
        cout << "소지하고 있는 무기가 없습니다." << endl;
        return;
    }

    for (int i = 0; i < weaponValue.size(); i++)
    {
        cout << i + 1 << ".무기 이름: " << weaponValue[i]->name << endl;
    }
    int num = 0;
    cout << "무기를 장착하려면 원하는 무기의 숫자를 입력해 주세요(취소하기 '0' 입력): " << num << endl;

    if (num == 0)
    {
        cout << "취소했습니다." << endl;
    }
    //장비를 장착할 때
    else if (num != 0) {
        EquipWeapon(weaponValue[num - 1]);
    }
}

void Inventory::DisplayArmor()
{
    //소지하고 있는 방어구가 없을 때
    if (armorValue.size() == 0) {
        cout << "소지하고 있는 방어구가 없습니다." << endl;
        return;
    }

    for (int i = 0; i < armorValue.size(); i++) {
        cout << i + 1 << ".방어구 이름: " << armorValue[i]->name << endl;
    }
    int num = 0;
    cout << "방어구를 장착하려면 원하는 방어구의 숫자를 입력해 주세요(취소하기 '0' 입력): " << num << endl;

    if (num == 0)
    {
        cout << "취소했습니다." << endl;
    }
    //장비를 장착할 때
    else if (num != 0) {
        EquipArmor(armorValue[num - 1]);
    }
}


void Inventory::EquipWeapon(Item* weapon)
{
    weapon->equip = true;

    //무기가 비어있을 때
    if (Character::Get()->GetEquipWeapon() == nullptr)
    {
        Character::Get()->SetEquipWeapon(weapon);
        Character::Get()->EquipStatus(weapon->attack, 0);
    }
    else
    {
        //기본 무기해제
        UnEquipWeapon();
        Character::Get()->UnEquipStatus(Character::Get()->GetEquipWeapon()->attack, 0);

        //새로운 무기 장착
        Character::Get()->SetEquipWeapon(weapon);
        Character::Get()->EquipStatus(weapon->attack, 0);
    }
}
void Inventory::EquipArmor(Item* armor)
{
    armor->equip = true;
    //방어구가 비어있을 때
    if (Character::Get()->GetEquipArmor() == nullptr)
    {
        Character::Get()->SetEquipArmor(armor);
        Character::Get()->EquipStatus(0, armor->health);
    }
    else
    {
        //기존 방어구 해제
        UnEquipArmor();
        Character::Get()->UnEquipStatus(0, Character::Get()->GetEquipArmor()->health); //기존 장비 해제 스탯변경

        //새로운 방어구 장착
        Character::Get()->SetEquipArmor(armor);
        Character::Get()->EquipStatus(0, armor->health);
    }
}
void Inventory::UnEquipWeapon()
{
    Character::Get()->GetEquipWeapon()->equip = false;
}
void Inventory::UnEquipArmor()
{
    Character::Get()->GetEquipArmor()->equip = false;
}

Inventory::~Inventory()
{
    for (auto& it : consumableValue) {
        delete it.first;
    }

    for (int i = 0; i < weaponValue.size(); i++)
    {
        delete weaponValue[i];
    }
    for (int i = 0; i < armorValue.size(); i++)
    {
        delete armorValue[i];
    }

    delete iveninstance;
    iveninstance = nullptr;
}