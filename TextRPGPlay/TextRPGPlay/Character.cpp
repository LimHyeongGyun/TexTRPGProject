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
    //���� instance�� �������� �ʾҴٸ�
    if (charInstance == nullptr)
    {
        charInstance = new Character(); //ĳ���� �������ֱ�
    }

    charInstance->name = name;

    return charInstance;
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
#pragma endregion

#pragma region Battle

int Character::Attack()
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
    UpgradeStatus();
}

void Character::UpgradeStatus()
{
    maxHealth += level * 20; //�ִ� ü�� ����
    attack = attack + level * 5; //���ݷ� ����

    RecoveryHP(maxHealth); //ü�� ȸ��
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