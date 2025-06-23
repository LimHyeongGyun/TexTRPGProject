#pragma once
#include<string>

class Character;
class Inventory;

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
	int value;
	int atack=0;
	int health =0;
	int heal=0;
	int upgradeAtack=0;
	int upgradeDefense=0;
	int upgradePhase = 0;
	int maxUpgradePhase = 9;
	bool equip=false;
public:
	Item(std::string name, ItemType type, int value, int Atack, int Defense, int Heal, bool Equip);
	//������


	std::string GetName() { return name; }
	//�̸� ��������

	int GetValue() { return value; }
	//���� ��������

	int GetAtack() { return atack; }
	//���ݷ�

	int GetUpgradeAtack() { return upgradeAtack; }
	//���ݷ� ��������

	ItemType GetType() { return type; }
	//Ÿ�� ��������


	int GeHealth() { return health; }
	//���� �� �߰�ü��

	int GetUpgradeAtack() { return upgradeAtack; }
	//���׷��̵� ���ݷ� ��������

	int GeHealth() { return health; }
	//���� �� �߰�ü��

	int GetUpgradeDefense() { return upgradeDefense; }
	//���׷��̵� ���� ��������

	int GetHeal() { return heal; }
	//ȸ���� ��������

	bool GetEquip() { equip; }
	//��� ���� �������� 

	void SetEquip(bool equip);
	//���� ��� ����

	int GetUpgradePhase() { return upgradePhase; }
	//��ȭ���� Ƚ�� ��������

	int GetMaxUbgradePhase() { return maxUpgradePhase; }
	//�ִ� ��ȭ Ƚ�� ��������

	void Use(Character* character);
	//ĳ���� ġ����


	void Use(Inventory* inventory);
	//�������

	void Upgrade();
	//���׷��̵� ��� ����

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
//    //��ȭ Ƚ�� ��������
//
//    int GetAttackPower() const { return attackPower; }
//    //���ݷ� ��������
//
//
//
//    void Upgrade();
//    //��ȭ ���
//        //��ȭ ��� 5������ ����
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
//    //��ȭ Ƚ�� ��������
//
//
//    int GetBonusHealth() const { return health; }
//    //���� ��������
//
//
//    void Upgrade();
//    //��ȭ ��� 5������ ����d
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
//    // ���⸦ �����մϴ�: `=nullptr` �⺻���� �����մϴ�!
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
