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

