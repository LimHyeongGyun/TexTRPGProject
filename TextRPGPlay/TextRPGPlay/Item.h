#pragma once
#include<string>
#include"Character.h"
#include "Inventory.h"


enum class ItemType {
	Armor,
	Weapon,
	Expendables,
	Potion
};

class Item {
private:
	std::string name;
	ItemType type= ItemType::Expendables;
	int Value;
	int Atack=0;
	int Defense=0;
	int Heal=0;
	int upgradeAtack=0;
	int upgradeDefense=0;
	int UpgradePhase = 0;
	int MaxUpgradePhase = 9;
	bool Equip=false;
public:
	Item(std::string name, ItemType type, int Value, int Atack, int Defense, int Heal, bool Equip);
	//생성자

	std::string GetName() { return name; }
	//이름 가져오기

	ItemType GetType() { return type; }
	//타입 가져오기
	int getAtack() { return Atack; }

	int getMaxUpgradePhase() { return Atack; }
	//공격력 가져오기

	int GetUpgradeAtack() { return upgradeAtack; }
	//업그레이드 공격력 가져오기

	int GetDefense() { return Defense; }
	//방어력 가져오기

	int GetUpgradeDefense() { return upgradeDefense; }
	//업그레이드 방어력 가져오기

	int GetHeal() { return Heal; }
	//회복량 가져오기

	bool GetEquip();
	//장비 여부 가져오기 

	void SetEquip(bool equip);
	//장비및 장비 해제

	int GetUpgradePhase() { return UpgradePhase; }
	//강화성공 횟수 가져오기

	void Use(Character* character);
	//캐릭터 치료기능


	void Use(Inventory* inventory);
	//장착기능

	void Upgrade();
	//업그레이드 기능 구현

	Item* Clone();
};












//#pragma once
//
//#include <string>
//#include "Character.h"
//#include "Inventory.h"
//
//class Character; // Forward declaration added
//class Inventory;
//
//enum class ItemType
//{
//    Expendable,
//    Weapon,
//    Armor
//};
//
//class Item
//{
//protected:
//    std::string name;
//    int price;
//    ItemType type;
//    bool equip=false;
//
//public:
//    Item(const std::string& name, int price, ItemType type) :name(name), price(price), type(type) {};
//    virtual void Use(Character* character, Inventory* inventory=nullptr) = 0;
//    virtual ~Item() = default;
//    virtual Item* Clone() const = 0;
//
//    std::string GetName() const { return name; }
//    int GetPrice() const { return price; }
//    ItemType GetType() const { return type; }
//    bool IsEquipped() const { return equip; }
//    void SetEquipped(bool equipped) { equip = equipped; }
//
//};
//
//
//class Weapon : public Item
//{
//private:
//    int upgradePhase = 0;
//    int attackPower;
//
//public:
//    Weapon(const std::string& name, int price, int attackPower);
//    void Use(Character* character, Inventory* inventory) override;
//    Item* Clone() const override;
//    int GetupgradePhase() const { return upgradePhase; }
//    //강화 횟수 가져오기
//
//    int GetAttackPower() const { return attackPower; }
//    //공격력 가져오기
//
//
//
//    void Upgrade();
//    //강화 기능
//        //강화 기능 5강까지 가능
//
//};
//
//class Armor : public Item
//{
//private:
//    int upgradePhase = 0;
//    int health;
//    bool equip;
//
//public:
//    Armor(const std::string& name, int price, int health);
//    void Use(Character* character, Inventory* inventory) override;
//    Item* Clone() const override;
//
//    int GetupgradePhase() const { return upgradePhase; }
//    //강화 횟수 가져오기
//
//
//    int GetBonusHealth() const { return health; }
//    //방어력 가져오기
//
//
//    void Upgrade();
//    //강화 기능 5강까지 가능d
//
//};
//
//class Expendable : public Item
//{
//protected:
//    int value;
//
//public:
//    Expendable(const std::string& name, int price, int value);
//
//    // 여기를 수정합니다: `=nullptr` 기본값을 제거합니다!
//    virtual void Use(Character* character, Inventory* inventory) = 0;
//    virtual Item* Clone() const = 0;
//
//    int GetValue() const { return value; }
//};
//
//
//class Potion : public Expendable
//{
//
//public:
//    Potion(const std::string& name, int price, int value);
//    void Use(Character* character, Inventory* inventory) override;
//    Item* Clone() const override;
//
//};
