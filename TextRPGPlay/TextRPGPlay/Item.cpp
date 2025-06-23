#include "Item.h"
#include<string>
#include<iostream>




Item::Item(std::string name, ItemType type, int Value, int Atack, int Defense, int Heal, bool Equip)
	:name(name), type(type),Value(Value), Atack(Atack), Defense(Defense), Heal(Heal), Equip(Equip) {}


//장비 여부 가져오기
bool Item::GetEquip()
{
	if (this->type == ItemType::Armor || this->type == ItemType::Weapon)
	{
		return this->Equip;
	}
	else
	{
		std::cout << "장비아이템이 아닙니다." << endl;
		return false;
	}
}

//장비 및 장비해제
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
		std::cout << "장비아이템이 아닙니다." << endl;
	}
}

//캐릭터 힐기능
void Item::Use(Character* character)
{
	if (this->type == ItemType::Potion)
	{
		character->RecoveryHP(Heal);
	}

	else
	{
		std::cout << "회복아이템이 아닙니다" << endl;
	}

}

//장비 업그레이드
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
		std::cout << "강화 가능 아이템이 아닙니다." << std::endl;
	}
}



Item* Item::Clone() {
	return new Item(*this); // 복사 생성자 호출
}

























//#include "Item.h"
//#include <string>
//#include "Character.h"
//#include "Inventory.h"
//
////=== Item 클래스 생성자 구현 ===//
//Item::Item(const std::string& name, int price, ItemType type)
//    : name(name), price(price), type(type) {
//}
//
////소모품 타입 생성자 구현
//Expendable::Expendable(const std::string& name, int price, int value)
//    : Item(name, price, ItemType::Expendable), value(value) {
//}
//
//
////=== HealingPotion 클래스 구현 ===//
//Potion::Potion(const std::string& name, int price, int healAmount)
//    : Expendable(name, price, healAmount) {
//}  
//
//void Potion::Use(Character* character, Inventory* inventory) {
//    if (character) {
//        character->RecoveryHP(this->GetValue());  // Expendable의 value 사용
//    }
//}
//
//
//
////=== Weapon 클래스 구현 ===//
//Weapon::Weapon(const std::string& name, int price, int attackPower)
//    : Item(name, price, ItemType::Weapon), attackPower(attackPower), equip(false) {
//}
//
//void Weapon::Use(Character* character, Inventory* inventory) {
//    if (inventory) {
//        // 캐릭터가 이 무기를 장착하도록 함
//        inventory->EquipWeapon(this);
//    }
//}
//
//
//
////=== Armor 클래스 구현 ===//
//Armor::Armor(const std::string& name, int price, int bonusHealth)
//    : Item(name, price, ItemType::Armor), health(bonusHealth), equip(false) {
//}
//
//void Armor::Use(Character* character, Inventory* inventory) {
//    if (inventory) {
//        // 캐릭터가 이 방어구를 장착하도록 함
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
//    // 예시: 최대 5강까지 가능하며, 강화마다 공격력이 5씩 증가
//    if (upgradePhase < 5) {
//        ++upgradePhase;
//        this->attackPower += 5;
//    }
//}
//
//
////복사생성자들 구현
//Item* Weapon::Clone() const {
//    return new Weapon(*this);
//}
//
//Item* Armor::Clone() const {
//    return new Armor(*this);
//}
//Item* Potion::Clone() const {
//    return new Potion(*this); // 복사 생성자 호출
//}
//
