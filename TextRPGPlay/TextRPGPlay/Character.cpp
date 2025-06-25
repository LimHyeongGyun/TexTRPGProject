#include <iostream>

#include "Character.h"
#include "Inventory.h"
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
    //���� instance�� �������� �ʾҴٸ�
    if (charInstance == nullptr)
    {
        charInstance = new Character(playerName); //ĳ���� �������ֱ�
    }

    return *charInstance;
}

void Character::DisplayStatus() const
{
    cout << "�÷��̾� ĳ���� �̸�: " << name << endl;
    cout << "�÷��̾� ����: " << level << endl;
    cout << "�÷��̾� ����ü��/�ִ�ü��: " << health << "/" << maxHealth << endl;
    cout << "�÷��̾� ���ݷ�: " << attack << endl;
    cout << "�÷��̾� ���� ����ġ/�������� �ʿ��� ����ġ: " << experience << "/" << needExperience << endl;
    cout << "�÷��̾� ���� ���: " << gold << endl;
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
    cout << "���Ϳ���" << damage << "�� ���ظ� �Ծ����ϴ�!";

    if (health <= 0) {
        health = 0;

        Die();
    }
    else {
        cout << "�÷��̾� ���� ü��: " << health << "/" << maxHealth << endl;
    }
}

void Character::RecoveryHP(int recoveryHp)
{
    health += recoveryHp; //ü�� ȸ��

    //���� ȸ���� �� ü���� �ִ� ü���� �Ѵ´ٸ�
    if (health > maxHealth) {
        health = maxHealth; //ü���� �ִ�ü������ ����
    }
}

void Character::Die()
{
    cout << "ü���� 0�̵Ǿ� �÷��̾� ĳ���Ͱ� ����Ͽ����ϴ�." << endl;
}
#pragma endregion

#pragma region Experience(Level)
void Character::GetExperience(int getExperience)
{
    experience += getExperience;

    while (experience >= needExperience)
    {
        experience -= needExperience; //�������� �ʿ��� ����ġ��ŭ ����
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
    baseHealth += level * 20; //�ִ� ü�� ����
    baseAttack = baseAttack + level * 5; //���ݷ� ����

    UpadatePlayerStatus(); //�÷��̾� ���� ������Ʈ
    RecoveryHP(maxHealth); //ü�� ȸ��
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
void Character::UseItem(int index) const
{
    Inventory::Get().DisplayConsumeItem();
}

void Character::BorrowGold(int getGold)
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