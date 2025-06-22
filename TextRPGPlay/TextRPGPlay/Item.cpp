#include "Item.h"
#include <string>
#include "Character.h"
#include "Inventory.h"

//=== Item 클래스 생성자 구현 ===//
Item::Item(const std::string& name, int price, ItemType type)
    : name(name), price(price), type(type) {
}
expendables::expendables(const std::string& name, int price, int value)
    : Item(name, price, ItemType::expendables), value(value) {
}


//=== HealingPotion 클래스 구현 ===//
Potion::Potion(const std::string& name, int price, int healAmount)
    : expendables(name, price, healAmount) {
}  // 상위 생성자에 넘김

void Potion::Use(Character* character, Inventory* inventory) {
    if (character) {
        character->RecoveryHP(this->GetValue());  // expendables의 value 사용
    }
}


Item* Potion::Clone() const {
    return new Potion(*this); // 복사 생성자 호출
}

//=== Weapon 클래스 구현 ===//
Weapon::Weapon(const std::string& name, int price, int attackPower)
    : Item(name, price, ItemType::Weapon), attackPower(attackPower), equip(false) {
}

void Weapon::Use(Character* character, Inventory* inventory) {
    if (inventory) {
        // 캐릭터가 이 무기를 장착하도록 함
        inventory->EquipWeapon(this);
    }
}

Item* Weapon::Clone() const {
    return new Weapon(*this);
}

//=== Armor 클래스 구현 ===//
Armor::Armor(const std::string& name, int price, int bonusHealth)
    : Item(name, price, ItemType::Armor), health(bonusHealth), equip(false) {
}

void Armor::Use(Character* character, Inventory* inventory) {
    if (inventory) {
        // 캐릭터가 이 방어구를 장착하도록 함
        inventory->EquipArmor(this);
    }
}

Item* Armor::Clone() const {
    return new Armor(*this);
}