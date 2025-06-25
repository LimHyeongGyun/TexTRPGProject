#pragma once
#include<vector>


class Item;
class Store
{
private:
	Store();
	static Store* instance;


public:
	Store(const Store&) = delete;
	Store& operator=(const Store&) = delete;
	static Store& Get();

	void SellExpendable();
	void SellOthers();
	void SellArmor();
	void SellWeapon();
	

	void Buy();
};


//std::unordered_map<Item*, int> expendableItems;
//std::unordered_map<Item*, int> otherItems;
//std::vector<Item*> weaponItems;
//std::vector<Item*> armorItems;
