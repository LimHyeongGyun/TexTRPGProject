#include "Store.h"
#include "ItemManager.h"
#include"Character.h"
#include"Inventory.h"
#include<iostream>
#include<string>
#include<vector>
using namespace std;

Store* Store::instance = nullptr;

// 2. Get() �Լ� ����
Store& Store::Get()
{
	// ���� �ν��Ͻ��� ���� ���ٸ�
	if (instance == nullptr)
	{
		// ���� ����
		instance = new Store();
	}
	// ������ �ν��Ͻ��� ������ ��ȯ
	return *instance;
}


Store::Store() {}

void Store::SellItem(Item* item)
{
	Character::Get().BorrowGold(item->GetValue()); //�� ����

	if (item->GetType() == ItemType::Weapon || item->GetType() == ItemType::Armor)
	{
		Inventory::Get().RemoveEquipItem(item);
	}
	else if (item->GetType() == ItemType::Expendables || item->GetType() == ItemType::Other)
	{
		Inventory::Get().RemoveNoneEquipItem({ {item->GetName(), 1} }, item->GetType());
	}

	cout << item->GetName() << "��(��) �Ǹ��߽��ϴ�." << endl;
	cout << "ȹ���� ���: " << item->GetValue() << endl;
}

void Store::Buy()
{
	vector<Item*>item;
	cout << "==================== ���� �Ǹ� ��� ====================" << endl;
	cout << "1: ���� �ռҵ� (Weapon) - ����: 55, ���ݷ�: 25" << endl;
	cout << "2: ���� ���� (Armor) - ����: 55, ����: 30" << endl;
	cout << "3: ��伮 �ռҵ� (Weapon) - ����: 150, ���ݷ�: 60" << endl;
	cout << "4: �罽 ���� (Armor) - ����: 198, ����: 70" << endl;
	cout << "5: ö �ռҵ� (Weapon) - ����: 308, ���ݷ�: 100" << endl;
	cout << "6: ö ���� (Armor) - ����: 308, ����: 100" << endl;
	cout << "7: ���� ���� ���� (Expendables) - ����: 55, ����: 50" << endl;
	cout << "8: ���� ���� ���� (Expendables) - ����: 132, ����: 100" << endl;
	cout << "9: ���� ���� ���� (Expendables) - ����: 275, ����: 200" << endl;
	cout << "========================================================" << endl;
	string name;
	cout << "�����Ͻ� ������ �̸��� �Է��� �ּ���:";
	cin >> name;
	Item* buyitem = ItemManager::Get().CreateItem(name);
	int a = buyitem->GetValue()+ static_cast<int>(buyitem->GetValue() * 0.1);
	if (buyitem != nullptr) {

		item.push_back(buyitem);
		if (Character::Get().GetGold() > a) {
			Character::Get().ConsumeGold(a);
			Character::Get().GetItem(item);
		}
	}

}