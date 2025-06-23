#include "Item.h"
#include<string>
#include<iostream>




Item::Item(std::string name, ItemType type, int Value, int Atack, int Defense, int Heal, bool Equip)
	:name(name), type(type),Value(Value), Atack(Atack), Defense(Defense), Heal(Heal), Equip(Equip) {}


//��� ���� ��������
bool Item::GetEquip()
{
	if (this->type == ItemType::Armor || this->type == ItemType::Weapon)
	{
		return this->Equip;
	}
	else
	{
		std::cout << "���������� �ƴմϴ�." << endl;
		return false;
	}
}

//��� �� �������
void Item::SetEquip()
{
	if (this->type == ItemType::Armor || this->type == ItemType::Weapon)
	{
		if (this->Equip == false)
		{
			this->Equip = true;
		}
		else
		{
			this->Equip = false;
		}
	}
	else
	{
		std::cout << "���������� �ƴմϴ�." << endl;
	}
}

//ĳ���� �����
void Item::Use(Character* character)
{
	if (this->type == ItemType::Potion)
	{
		character->RecoveryHP(Heal);
	}

	else
	{
		std::cout << "ȸ���������� �ƴմϴ�" << endl;
	}

}

//��� ���׷��̵�
void Item::Upgrade()
{
	if(this->type == ItemType::Armor || this->type == ItemType::Weapon)
	{
		this->UpgradePhase++;

		if (this->type == ItemType::Armor)
		{
			this->Defense = this->Defense + (10 * this->UpgradePhase);
		}

		else
		{
			this->Atack = this->Atack + (5 * this->UpgradePhase);
		}

	}
	else
	{
		std::cout << "��ȭ ���� �������� �ƴմϴ�." << std::endl;
	}
}



Item* Item::Clone() {
	return new Item(*this); // ���� ������ ȣ��
}

























//#include "Item.h"
//#include <string>
//#include "Character.h"
//#include "Inventory.h"
//
////=== Item Ŭ���� ������ ���� ===//
//Item::Item(const std::string& name, int price, ItemType type)
//    : name(name), price(price), type(type) {
//}
//
////�Ҹ�ǰ Ÿ�� ������ ����
//Expendable::Expendable(const std::string& name, int price, int value)
//    : Item(name, price, ItemType::Expendable), value(value) {
//}
//
//
////=== HealingPotion Ŭ���� ���� ===//
//Potion::Potion(const std::string& name, int price, int healAmount)
//    : Expendable(name, price, healAmount) {
//}  
//
//void Potion::Use(Character* character, Inventory* inventory) {
//    if (character) {
//        character->RecoveryHP(this->GetValue());  // Expendable�� value ���
//    }
//}
//
//
//
////=== Weapon Ŭ���� ���� ===//
//Weapon::Weapon(const std::string& name, int price, int attackPower)
//    : Item(name, price, ItemType::Weapon), attackPower(attackPower), equip(false) {
//}
//
//void Weapon::Use(Character* character, Inventory* inventory) {
//    if (inventory) {
//        // ĳ���Ͱ� �� ���⸦ �����ϵ��� ��
//        inventory->EquipWeapon(this);
//    }
//}
//
//
//
////=== Armor Ŭ���� ���� ===//
//Armor::Armor(const std::string& name, int price, int bonusHealth)
//    : Item(name, price, ItemType::Armor), health(bonusHealth), equip(false) {
//}
//
//void Armor::Use(Character* character, Inventory* inventory) {
//    if (inventory) {
//        // ĳ���Ͱ� �� ���� �����ϵ��� ��
//        inventory->EquipArmor(this);
//    }
//}
//
//void Armor::Upgrade() {
//    if (upgradePhase < 6) {
//        ++upgradePhase;
//        this->health += 5;
//    }
//}
//
//void Weapon::Upgrade() {
//    // ����: �ִ� 5������ �����ϸ�, ��ȭ���� ���ݷ��� 5�� ����
//    if (upgradePhase < 5) {
//        ++upgradePhase;
//        this->attackPower += 5;
//    }
//}
//
//
////��������ڵ� ����
//Item* Weapon::Clone() const {
//    return new Weapon(*this);
//}
//
//Item* Armor::Clone() const {
//    return new Armor(*this);
//}
//Item* Potion::Clone() const {
//    return new Potion(*this); // ���� ������ ȣ��
//}
//
