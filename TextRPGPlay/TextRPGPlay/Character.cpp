#include <iostream>
#include "Character.h"
#include "Inventory.h"

Character* Character::charInstance = nullptr;

#pragma region PlayerInformation

Character::Character() {
    name = name;
    level = 1;
    maxLevel = 10;
    maxHealth = 200;
    health = maxHealth;
    attack = 30;
    experience = 0;
    needExperience = 100;
    gold = 0;

    equipWeapon = nullptr;
    equipArmor = nullptr;
}

Character* Character::Get(string name)
{
    //만약 instance가 생성되지 않았다면
    if (charInstance == nullptr)
    {
        charInstance = new Character(); //캐릭터 생성해주기
    }

    charInstance->name = name;

    return charInstance;
}

void Character::DisplayStatus() const
{
    cout << "플레이어 캐릭터 이름: " << name << endl;
    cout << "플레이어 레벨: " << level << endl;
    cout << "플레이어 현재체력/최대체력: " << health << "/" << maxHealth << endl;
    cout << "플레이어 공격력: " << attack << endl;
    cout << "플레이어 현재 경험치/레벨업에 필요한 경험치: " << experience << "/" << needExperience << endl;
    cout << "플레이어 소지 골드: " << gold << endl;
}

string Character::GetName() const
{
    return name;
}
#pragma endregion

#pragma region Battle

int Character::Attack()
{
    return attack;
}

void Character::TakeDamage(int damage)
{
    health -= damage;
    cout << "몬스터에게" << damage << "의 피해를 입었습니다!";

    if (health <= 0) {
        health = 0;

        Die();
    }
    else {
        cout << "플레이어 남은 체력: " << health << "/" << maxHealth << endl;
    }
}

void Character::RecoveryHP(int recoveryHp)
{
    health += recoveryHp; //체력 회복

    //만약 회복한 후 체력이 최대 체력을 넘는다면
    if (health > maxHealth) {
        health = maxHealth; //체력을 최대체력으로 조정
    }
}

void Character::Die()
{
    cout << "체력이 0이되어 플레이어 캐릭터가 사망하였습니다." << endl;
}
#pragma endregion

#pragma region Experience(Level)
void Character::GetExperience(int getExperience)
{
    experience += getExperience;

    while (experience >= needExperience)
    {
        experience -= needExperience; //레벨업에 필요한 경험치만큼 제거
        LevelUp();
    }
}

void Character::LevelUp()
{
    if (level < maxLevel) {
        level += 1;
    }
    UpgradeStatus();
}

void Character::UpgradeStatus()
{
    maxHealth += level * 20; //최대 체력 증가
    attack = attack + level * 5; //공격력 증가

    RecoveryHP(maxHealth); //체력 회복
}
#pragma endregion

#pragma region Equipment
Item* Character::GetEquipWeapon()
{
    return equipWeapon;
}
Item* Character::GetEquipArmor()
{
    return equipArmor;
}

void Character::SetEquipWeapon(Item* weapon)
{
    equipWeapon = weapon;
}
void Character::SetEquipArmor(Item* armor)
{
    equipArmor = armor;
}

void Character::EquipStatus(int getAttack, int getHealth)
{
    attack += getAttack;
    maxHealth += getHealth;
}

void Character::UnEquipStatus(int getAttack, int getHealth)
{
    attack -= getAttack;
    maxHealth -= getHealth;
}


#pragma endregion

#pragma region Item & Shop

void Character::GetItem(Item* getItem, int num)
{
    Inventory::Get()->ClassificationItem(getItem, num);
}
void Character::UseItem(int index)
{
    Inventory::Get()->DisplayConsumeItem();
}

void Character::GetGold(int getGold)
{
    gold += getGold;
}

void Character::ConsumeGold(int consumeGold)
{
    gold -= consumeGold;
}

void Character::VisitShop()
{

}
#pragma endregion

Character::~Character()
{
    delete charInstance;
    charInstance = nullptr;
}