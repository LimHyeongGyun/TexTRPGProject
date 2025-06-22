#include "Item.h"
#include <string>
#include "Character.h"
#include "Inventory.h"

//=== Item Ŭ���� ������ ���� ===//
Item::Item(const std::string& name, int price, ItemType type)
    : name(name), price(price), type(type) {
}
expendables::expendables(const std::string& name, int price, int value)
    : Item(name, price, ItemType::expendables), value(value) {
}


//=== HealingPotion Ŭ���� ���� ===//
Potion::Potion(const std::string& name, int price, int healAmount)
    : expendables(name, price, healAmount) {
}  // ���� �����ڿ� �ѱ�

void Potion::Use(Character* character, Inventory* inventory) {
    if (character) {
        character->RecoveryHP(this->GetValue());  // expendables�� value ���
    }
}



//=== Weapon Ŭ���� ���� ===//
Weapon::Weapon(const std::string& name, int price, int attackPower)
    : Item(name, price, ItemType::Weapon), attackPower(attackPower), equip(false) {
}

void Weapon::Use(Character* character, Inventory* inventory) {
    if (inventory) {
        // ĳ���Ͱ� �� ���⸦ �����ϵ��� ��
        inventory->EquipWeapon(this);
    }
}



//=== Armor Ŭ���� ���� ===//
Armor::Armor(const std::string& name, int price, int bonusHealth)
    : Item(name, price, ItemType::Armor), health(bonusHealth), equip(false) {
}

void Armor::Use(Character* character, Inventory* inventory) {
    if (inventory) {
        // ĳ���Ͱ� �� ���� �����ϵ��� ��
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
    // ����: �ִ� 5������ �����ϸ�, ��ȭ���� ���ݷ��� 5�� ����
    if (upgradePhase < 5) {
        ++upgradePhase;
        this->attackPower +=5;
    }
}


//��������ڵ� ����
Item* Weapon::Clone() const {
    return new Weapon(*this);
}

Item* Armor::Clone() const {  
    return new Armor(*this);  
}
Item* Potion::Clone() const {
    return new Potion(*this); // ���� ������ ȣ��
}
