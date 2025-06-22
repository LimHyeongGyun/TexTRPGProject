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
    int attackPower;
    bool equip;

public:
    Weapon(const std::string& name, int price, int attackPower);
    void Use(Character* character, Inventory* inventory) override;
    Item* Clone() const override;

    int GetAttackPower() const { return attackPower; }
    bool IsEquipped() const { return equip; }
    void SetEquipped(bool equipped) { equip = equipped; }

};

class Armor : public Item {
private:
    int health;
    bool equip;

public:
    Armor(const std::string& name, int price, int health);
    void Use(Character* character, Inventory* inventory) override;
    Item* Clone() const override;

    int GetBonusHealth() const { return health; }
    bool IsEquipped() const { return equip; }
    void SetEquipped(bool equipped) { equip = equipped; }
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
