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

void Armor::Upgrade() {
    if (upgradePhase < 6) {
        ++upgradePhase;
        this->health +=5;
    }
}

void Weapon::Upgrade() {
    // 예시: 최대 5강까지 가능하며, 강화마다 공격력이 5씩 증가
    if (upgradePhase < 5) {
        ++upgradePhase;
        this->attackPower +=5;
    }
}


//복사생성자들 구현
Item* Weapon::Clone() const {
    return new Weapon(*this);
}

Item* Armor::Clone() const {  
    return new Armor(*this);  
}
Item* Potion::Clone() const {
    return new Potion(*this); // 복사 생성자 호출
}
