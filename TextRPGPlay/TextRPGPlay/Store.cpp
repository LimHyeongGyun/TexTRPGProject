#include "Store.h"
#include "ItemManager.h"
#include"Character.h"
#include"Inventory.h"
#include "GameManager.h"
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

void Store::EnteredStore()
{
	int sub;
	while (true)
	{
		cout << "0. 돌아가기\n 1. 구매\n2. 판매\n입력 >> ";
		cin >> sub;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << GameManager::Get().WrongInputMessage();
			continue;
		}

		if (sub == 0)
		{
			return;
		}
		else if (sub == 1)
		{
			Store::Get().Buy();
			break;
		}
		else if (sub == 2)
		{
			Inventory::Get().DisplayInventory(Inventory::Get().sell);
			break;
		}
		else
		{
			cout << GameManager::Get().WrongInputMessage();
		}
	}
}

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

	cout << item->GetName() << "을(를) 판매했습니다." << endl;
	cout << "획득한 골드: " << item->GetValue() << endl;
}

void Store::Buy()
{
	while (true) {
		vector<Item*>item;
		cout << "==================== 상점 판매 목록 ====================" << endl;
		cout << "1: 나무롱소드 (Weapon) - 가격: 55, 공격력: 25" << endl;
		cout << "2: 가죽갑옷 (Armor) - 가격: 55, 방어력: 30" << endl;
		cout << "3: 흑요석롱소드 (Weapon) - 가격: 150, 공격력: 60" << endl;
		cout << "4: 사슬갑옷 (Armor) - 가격: 198, 방어력: 70" << endl;
		cout << "5: 철롱소드 (Weapon) - 가격: 308, 공격력: 100" << endl;
		cout << "6: 철갑옷 (Armor) - 가격: 308, 방어력: 100" << endl;
		cout << "7: 소형힐링포션 (Expendables) - 가격: 55, 힐량: 50" << endl;
		cout << "8: 중형힐링포션 (Expendables) - 가격: 132, 힐량: 100" << endl;
		cout << "9: 대형힐링포션 (Expendables) - 가격: 275, 힐량: 200" << endl;
		cout << "========================================================" << endl;
		string name;
		cout << "구매하실 아이템 이름을 입력해 주세요:";
		cout << "상점 나가기:p";
		cout << endl;
		cin >> name;

		Item* buyitem = ItemManager::Get().CreateItem(name);
		if (buyitem == nullptr) {
			if (name == "p") {
				return;
			}
			cout << "존재하지 않는 아이템입니다. 다시 입력해 주세요." << endl;
			continue;
		}

		int a = buyitem->GetValue() + static_cast<int>(buyitem->GetValue() * 0.1);


		item.push_back(buyitem);
		if (Character::Get().GetGold() > a) {
			Character::Get().ConsumeGold(a);
			Character::Get().GetItem(item);
		}

	}

}