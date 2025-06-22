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

	//�κ��丮 ����
	void DisplayWeapon();
	void DisplayArmor();

	//������ ���
	void EquipWeapon(Item* weapon); //���� ����
	void EquipArmor(Item* armor); //�� ����
	void UnEquipWeapon(); //�� ����
	void UnEquipArmor(); //���� ����
public:
	static Inventory* Get(); //�̱��� �ν��Ͻ�

	unordered_map<Item*, int> expendableItems;
	vector<Item*> weaponItems;
	vector<Item*> armorItems;
	vector<Item*> otherItems;

	//�κ��丮 ����
	void ClassificationItem(vector<Item*> items); //ȹ���� �������� �з��ؼ� �κ��丮�� �ֱ�
	void DisplayInventory();	
	void DisplayConsumeItem();

	~Inventory();
};