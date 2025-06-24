#pragma once

#include<string>
#include<vector>
#include<unordered_map>

class Character;
class Item;
class Forge;

class Inventory {
private:
	static Inventory* iveninstance;

	//인벤토리 관리
	void DisplayWeapon();
	void DisplayArmor();

	//아이템 사용
	void UnEquipWeapon(); //방어구 해제
	void UnEquipArmor(); //무기 해제
public:
	static Inventory& Get(); //싱글턴 인스턴스

	std::unordered_map<Item*, int> expendableItems;
	std::unordered_map<Item*, int> otherItems;
	std::vector<Item*> weaponItems;
	std::vector<Item*> armorItems;

	void EquipWeapon(Item* weapon); //무기 장착
	void EquipArmor(Item* armor); //방어구 장착

	//인벤토리 관리
	void ClassificationItem(std::vector<Item*> items); //획득한 아이템을 분류해서 인벤토리에 넣기
	void DisplayInventory();	
	void DisplayConsumeItem();
	void RemoveItem(const std::unordered_map<std::string, int>& materials); //아이템 제거

	~Inventory();
};