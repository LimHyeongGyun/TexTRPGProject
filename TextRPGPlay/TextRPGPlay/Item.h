#pragma once

#include <string>

class Character; // Forward declaration added
class Inventory;

enum class ItemType {
    expendables,
    Weapon,
    Armor 
};

class Item{
protected:
    std::string name;
    int price;
    ItemType type;

public:
    Item(const std::string& name, int price, ItemType type) :name(name), price(price), type(type) {};
    virtual void Use(Character* character, Inventory* inventory) = 0;
    virtual ~Item() = default;
    virtual Item* Clone() const = 0;

    std::string GetName() const { return name; }
    int GetPrice() const { return price; }
    ItemType GetType() const { return type; }

};


class Weapon : public Item {
private:
    int upgradePhase = 0;
    int attackPower;
    bool equip;

public:
    Weapon(const std::string& name, int price, int attackPower);
    void Use(Character* character, Inventory* inventory) override;
    Item* Clone() const override;

    int GetupgradePhase() const { return upgradePhase; }
    //강화 횟수 가져오기

    int GetAttackPower() const { return attackPower; }
    //공격력 가져오기

    bool IsEquipped() const { return equip; }
    //착용된 아이템인지 확인

    void SetEquipped(bool equipped) { equip = equipped; }
    //착용 상태 변경

    void Upgrade();
    //강화 기능
       //강화 기능 5강까지 가능

};

class Armor : public Item {
private:
    int upgradePhase = 0;
    int health;
    bool equip;

public:
    Armor(const std::string& name, int price, int health);
    void Use(Character* character, Inventory* inventory) override;
    Item* Clone() const override;

    int GetupgradePhase() const { return upgradePhase; }
    //강화 횟수 가져오기


    int GetBonusHealth() const { return health; }
    //방어력 가져오기

    bool IsEquipped() const { return equip; }
    //착용된 아이템인지 확인

    void SetEquipped(bool equipped) { equip = equipped; }
    //착용 상태 변경

    void Upgrade();
    //강화 기능 5강까지 가능

};

class expendables : public Item {
protected:
    int value;

public:
    expendables(const std::string& name, int price, int value);

    virtual void Use(Character* character, Inventory* inventory) = 0;
    virtual Item* Clone() const = 0;

    int GetValue() const { return value; }
};

class Potion : public expendables {

public:
    Potion(const std::string& name, int price, int value);
    void Use(Character* character, Inventory* inventory) override;
    Item* Clone() const override;

};
