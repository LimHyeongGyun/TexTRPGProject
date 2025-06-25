#pragma once

#include<string>
#include<vector>
#include<unordered_map>

class Character;
class Item;
class Forge;
enum class ItemType;

class Inventory {
private:
	static Inventory* iveninstance;

	//�κ��丮 ����
	void DisplayWeapon(std::string func);
	void DisplayArmor(std::string func);

	//������ ���
	void UnEquipWeapon(); //�� ����
	void UnEquipArmor(); //���� ����
public:
	static Inventory& Get(); //�̱��� �ν��Ͻ�

	std::string use = "use";
	std::string sell = "sell";

	std::unordered_map<Item*, int> expendableItems;
	std::unordered_map<Item*, int> otherItems;
	std::vector<Item*> weaponItems;
	std::vector<Item*> armorItems;

	void EquipWeapon(Item* weapon); //���� ����
	void EquipArmor(Item* armor); //�� ����

	//�κ��丮 ����
	void ClassificationItem(std::vector<Item*> items); //ȹ���� �������� �з��ؼ� �κ��丮�� �ֱ�
	void DisplayInventory(std::string func = " ");
	void DisplayConsumeItem(std::string func);
	void DIsplayOtherItem(std::string func);
	void RemoveEquipItem(Item* equip);
	void RemoveNoneEquipItem(const std::unordered_map<std::string, int>& materials, ItemType type); //������ ����

	~Inventory();
};