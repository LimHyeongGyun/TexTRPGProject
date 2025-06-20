#pragma once

#include<string>
#include<vector>
#include<unordered_map>

using namespace std;

class Character;
class Item;

class Inventory {
private:
	static Inventory* iveninstance;
public:
	static Inventory* Get(string name = " "); //싱글턴 인스턴스

	unordered_map<Item*, int> potionValue;
	vector<Item*> weaponValue;
	vector<Item*> armorValue;

	//인벤토리 관리
	void ClassificationItem(Item* item, int num); //획득한 아이템을 분류해서 인벤토리에 넣기
	void DisplayInventory();
	void DisplayConsumeItem();
	void DisplayWeapon();
	void DisplayArmor();

	//아이템 사용
	void EquipWeapon(Item* weapon); //무기 장착
	void EquipArmor(Item* armor); //방어구 장착
	void UnEquipWeapon(); //방어구 해제
	void UnEquipArmor(); //무기 해제

	~Inventory();
};