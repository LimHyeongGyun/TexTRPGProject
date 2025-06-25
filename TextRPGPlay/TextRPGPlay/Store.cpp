#include "Store.h"
#include "ItemManager.h"
#include"Character.h"
#include"Inventory.h"
#include<iostream>
#include<string>
#include<vector>
using namespace std;

Store* Store::instance = nullptr;

// 2. Get() 함수 구현
Store& Store::Get()
{
	// 만약 인스턴스가 아직 없다면
	if (instance == nullptr)
	{
		// 새로 생성
		instance = new Store();
	}
	// 유일한 인스턴스의 참조를 반환
	return *instance;
}


Store::Store() {}


void Store::SellOthers() {
	string name;
	int count;
	cout << "판매할 아이템 이름을 입력해 주세요:";
	cin >> name;
	cout << "판매할 수량을 입력해 주세요";
	cin >> count;
	auto& others = Inventory::Get().otherItems;
	if (others.size() == 0) {
		std::cout << "인벤토리가 비어있습니다." << std::endl;
		return;

	}
	for (auto it = others.begin(); it != others.end(); ++it)
	{

		if (it->first->GetName() == name)
		{
			if (it->second < count)

			{
				cout << "수량이 부족합니다" << endl;
				break;
			}
			int price = it->first->GetValue() * count;
			Character::Get().BorrowGold(price);

			//아이템 제거
			std::unordered_map<std::string, int> removeMap;
			removeMap[name] = count;
			ItemType i = ItemType::Other;
			Inventory::Get().RemoveNoneEquipItem(removeMap,i);
			std::cout << price << " 골드를 획득했습니다!" << std::endl;
			break;
		}

	}
};
void Store::SellExpendable() {
	string name;
	int count;
	cout << "판매할 아이템 이름을 입력해 주세요:";
	cin >> name;
	cout << "판매할 수량을 입력해 주세요";
	cin >> count;

	auto& others = Inventory::Get().expendableItems;
	if (others.size() == 0) {
		std::cout << "인벤토리가 비어있습니다." << std::endl;
		return;
	}
	for (auto it = others.begin(); it != others.end(); ++it)
	{


		if (it->first->GetName() == name)
		{
			if (it->second < count)

			{
				cout << "수량이 부족합니다" << endl;
				break;
			}
			int price = it->first->GetValue() * count;
			Character::Get().BorrowGold(price);

			//아이템 제거
			std::unordered_map<std::string, int> removeMap;
			removeMap[name] = count;
			ItemType i = ItemType::Other;
			Inventory::Get().RemoveNoneEquipItem(removeMap, i);
			std::cout << price << " 골드를 획득했습니다!" << std::endl;
			break;
		}

	}
};

void Store::SellArmor() {
	string name;
	int count;
	cout << "판매할 아이템 이름을 입력해 주세요:";
	cin >> name;
	for (int i = 0 ; i<Inventory::Get().armorItems.size();i++)
	{
		if (Inventory::Get().armorItems.empty()) {
			std::cout << "인벤토리가 비어있습니다" << endl;
			break;
		}
		if (Inventory::Get().armorItems[i]->GetName() ==name )
		{
			
			int price = Inventory::Get().armorItems[i]->GetValue();
			Character::Get().BorrowGold(price);
			Inventory::Get().armorItems.erase(Inventory::Get().armorItems.begin() + i);
			std::cout << price << " 골드를 획득했습니다!" << std::endl;
			break;
		}

	}
};




void Store::SellWeapon() {
	string name;
	int count;
	cout << "판매할 아이템 이름을 입력해 주세요:";
	cin >> name;
	for (int i = 0; i < Inventory::Get().weaponItems.size(); i++)
	{
		if (Inventory::Get().weaponItems.empty()) {
			std::cout << "인벤토리가 비어있습니다" << endl;
			break;
		}
		if (Inventory::Get().weaponItems[i]->GetName() == name)
		{

			int price = Inventory::Get().weaponItems[i]->GetValue();
			Character::Get().BorrowGold(price);
			Inventory::Get().weaponItems.erase(Inventory::Get().weaponItems.begin() + i);
			std::cout << price << " 골드를 획득했습니다!" << std::endl;
			break;
		}

	}
};


void Store::SellItem(Item* item)
{
	Character::Get().BorrowGold(item->GetValue()); //돈 수익
	if (item->GetType() == ItemType::Weapon || item->GetType() == ItemType::Armor)
	{
		Inventory::Get().RemoveEquipItem(item);
	}
	else if (item->GetType() == ItemType::Expendables || item->GetType() == ItemType::Other)
	{
		Inventory::Get().RemoveNoneEquipItem({ {item->GetName(), 1} }, item->GetType());
	}
}

void Store::Buy()
{
	vector<Item*>item;
	cout << "==================== 상점 판매 목록 ====================" << endl;
	cout << "1: 나무 롱소드 (Weapon) - 가격: 55, 공격력: 25" << endl;
	cout << "2: 가죽 갑옷 (Armor) - 가격: 55, 방어력: 30" << endl;
	cout << "3: 흑요석 롱소드 (Weapon) - 가격: 150, 공격력: 60" << endl;
	cout << "4: 사슬 갑옷 (Armor) - 가격: 198, 방어력: 70" << endl;
	cout << "5: 철 롱소드 (Weapon) - 가격: 308, 공격력: 100" << endl;
	cout << "6: 철 갑옷 (Armor) - 가격: 308, 방어력: 100" << endl;
	cout << "7: 소형 힐링 포션 (Expendables) - 가격: 55, 힐량: 50" << endl;
	cout << "8: 중형 힐링 포션 (Expendables) - 가격: 132, 힐량: 100" << endl;
	cout << "9: 대형 힐링 포션 (Expendables) - 가격: 275, 힐량: 200" << endl;
	cout << "========================================================" << endl;
	string name;
	cout << "구매하실 아이템 이름을 입력해 주세요:";
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