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

	//�κ��丮 ����
	void DisplayWeapon();
	void DisplayArmor();

	//������ ���
	void UnEquipWeapon(); //�� ����
	void UnEquipArmor(); //���� ����
public:
	static Inventory& Get(); //�̱��� �ν��Ͻ�

	std::unordered_map<Item*, int> expendableItems;
	std::unordered_map<Item*, int> otherItems;
	std::vector<Item*> weaponItems;
	std::vector<Item*> armorItems;

	void EquipWeapon(Item* weapon); //���� ����
	void EquipArmor(Item* armor); //�� ����

	//�κ��丮 ����
	void ClassificationItem(std::vector<Item*> items); //ȹ���� �������� �з��ؼ� �κ��丮�� �ֱ�
	void DisplayInventory();	
	void DisplayConsumeItem();
	void RemoveItem(const std::unordered_map<std::string, int>& materials); //������ ����

	~Inventory();
};