#include <iostream>

#include "Character.h"
#include "Inventory.h"
#include "Store.h"
#include "Item.h"

using namespace std;

Character* Character::charInstance = nullptr;

#pragma region PlayerInformation

Character::Character(string playerName) {
    name = playerName;
    level = 1;
    maxLevel = 10;
    baseHealth = 200;
    maxHealth = baseHealth;
    health = maxHealth;
    baseAttack = 30;
    attack = baseAttack;
    experience = 0;
    needExperience = 100;
    gold = 0;

    equipWeapon = nullptr;
    equipArmor = nullptr;
}

Character& Character::Get(string playerName)
{
    //만약 instance가 생성되지 않았다면
    if (charInstance == nullptr)
    {
        charInstance = new Character(playerName); //캐릭터 생성해주기
    }

    return *charInstance;
}

void Character::DisplayStatus() const
{
    cout << "\n===== 플레이어 상태창 =====" << endl;
    cout << "플레이어 캐릭터 이름: " << name << endl;
    cout << "플레이어 레벨: " << level << endl;
    cout << "플레이어 현재체력/최대체력: " << health << "/" << maxHealth << endl;
    cout << "플레이어 공격력: " << attack << endl;
    cout << "플레이어 현재 경험치/레벨업에 필요한 경험치: " << experience << "/" << needExperience << endl;
    cout << "플레이어 소지 골드: " << gold << "\n" << endl;
}

string Character::GetName() const
{
    return name;
}

int Character::GetHealth() const
{
    return health;
}

int Character::GetLevel() const
{
    return level;
}

int Character::GetGold() const
{
    return gold;
}

void Character::UpadatePlayerStatus()
{
    if (equipArmor != nullptr)
    {
        maxHealth = baseHealth + equipArmor->GetBonusHealth();
    }
    if (equipWeapon != nullptr)
    {
        attack = baseAttack + equipWeapon->GetAttack();
    }
    else if (equipArmor == nullptr && equipWeapon == nullptr)
    {
        maxHealth = baseHealth;
        attack = baseAttack;
    }
    
}
#pragma endregion

#pragma region Battle

int Character::Attack() const
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
        cout << "플레이어 남은 체력: " << health << "/" << maxHealth << "\n" << endl;
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
    LevelUpStatus();
}

void Character::LevelUpStatus()
{
    baseHealth += level * 20; //최대 체력 증가
    baseAttack = baseAttack + level * 5; //공격력 증가

    UpadatePlayerStatus(); //플레이어 스탯 업데이트
    RecoveryHP(maxHealth); //체력 회복
}

#pragma endregion

#pragma region Equipment
Item* Character::GetEquipWeapon() const
{
    return equipWeapon;
}
Item* Character::GetEquipArmor() const
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

#pragma endregion

#pragma region Item & Shop

void Character::GetItem(vector<Item*> getItems) const
{
    Inventory::Get().ClassificationItem(getItems);
}
void Character::UseItem() const
{
    Inventory::Get().DisplayExpendableItem(Inventory::Get().use);
}

void Character::BorrowGold(int getGold)
{
    gold += getGold;
}

void Character::ConsumeGold(int consumeGold)
{
    gold -= consumeGold;
}
#pragma endregion

Character::~Character()
{
    delete charInstance;
    charInstance = nullptr;
}