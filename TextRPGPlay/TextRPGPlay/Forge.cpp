#include <iostream>
#include "Forge.h"
#include "item.h"
#include "Inventory.h"

using namespace std;

void Forge::EnteredForge()
{
	int num;

	cin.ignore();
	cout << "드워프 대장장이 불카누스: 무슨 볼일이 있어서 왔나?" << endl;

	while (true)
	{
		cout << "0.대장간 떠나기" << endl;
		cout << "1.장비강화" << endl;
		cout << "2.장비제작 " << endl;
		cout << "3.조합식 확인하기" << endl;
		cout << "4.???" << endl;
		cout << "진행할 작업의 번호를 입력해주세요: ";
		cin >> num;

		if (num == 0)
		{
			cout << "드워프 대장장이 불카누스: 드래곤을 잡으면 장비를 제작하러 오게!" << endl;
			cout << "드워프 대장장이 불카누스: 내가 아주 멋진 것을 만들어주지!" << endl;
			break;
		}
		else if (num == 1)
		{
			DisplayUpgradeEquipment();
		}
		else if (num == 2)
		{
			MakeEquipment();
		}
		else if (num == 3)
		{
			DisplayEquipmentRecipe();
		}
		else if (num == 4)
		{
			Item* test; //나중에 DB에서 끌어다주기
			unordered_map<Item*, int>::iterator dragonToken = Inventory::Get()->consumableValue.find(test);
			//드래곤을 잡은 증표가 없을때
			if (dragonToken == Inventory::Get()->consumableValue.end())
			{

			}
			//드래곤을 잡은 증표가 있을때
			else
			{

			}
		}
		else
		{
			cout << "진행 가능한 작업만 입력해주세요." << endl;
		}
	}
}

void Forge::DisplayUpgradeEquipment()
{
	cout << "==============강화확률==============" << endl;
	for (int i = 0; i < UP.per.size(); i++)
	{
		cout << i << "강 강화확률:" << UP.per[i] << endl;
	}

	int category = 0;
	cout << "강화할 장비 번호를 입력해주세요.[1.무기, 2.방어구]: " << endl;
	cin >> category;

	vector<Item*> itemList; //장비 인벤토리를 저장할 변수

	switch (category)
	{
		case 1:
			itemList = Inventory::Get()->weaponValue;
			cout << "내가 소지한 무기 리스트" << endl;
			break;
		case2:
			itemList = Inventory::Get()->armorValue;
			cout << "내가 소지한 방어구 리스트" << endl;
			break;
		default:
			cout << "잘못된 번호입니다." << endl;
			return;
	}

	//강화할 장비가 없을때
	if (itemList.empty()) {
		cout << "강화할 수 있는 장비가 없습니다." << endl;
		return;
	}

	//장비 리스트 출력
	for (int i = 0; i < itemList.size(); i++) {
		cout << i + 1 << "." << itemList[i]->name << endl;
	}

	int selected = 0; //장비 순서
	while (true)
	{
		cout << "강화를 진행할 장비의 번호를 입력해주세요: ";
		cin >> selected;

		//유효성 검사
		if (selected <= 0 || selected > static_cast<int>(itemList.size()))
		{
			cout << "다시 입력해 주세요" << endl;
			system("pause");
		}
	}
	
	//결과
	pair<Item*, string> result = Upgrade(itemList[selected - 1]);

	cout << result.first->name << "의 강화가" << result.second << "했습니다." << endl;
	
	//강화가 성공했을 때
	if (result.second == "성공") {
		cout << "강화 단계: " << result.first->upgradePhase - 1 << "=>" << result.first->upgradePhase << endl;
		if (result.first->itemType == Weapon)
		{
			cout << "강화 후 아이템 수치" << result.first->attack - result.first->upgradeAtkValue << "=>" << result.first->attack << endl;
		}
		else if (result.first->itemType == Armor)
		{
			cout << "강화 후 아이템 수치" << result.first->health - result.first->upgradeHpValue << "=>" << result.first->health << endl;
		}
	}
	//강화가 실패했을 때
	else if (result.second == "실패")
	{
		cout << "강화에 실패했습니다. " << endl;
	}
}

int Forge::UpgradePercent(int upValue)
{
	return UP.per[upValue];
}

pair<Item*, string> Forge::Upgrade(Item* equipment)
{
	string result;
	int successRate = UpgradePercent(equipment->upgradePhase);
	int roll = rand() % 100;

	if (roll < successRate)
	{
		result = "성공";
		equipment->upgradePhase++;
		if (equipment->itemType == Weapon) equipment->attack += equipment->upgradeAtkValue;
		else if (equipment->itemType == Armor) equipment->health += equipment->upgradeHpValue;
	}
	else
	{
		result = "실패";
	}

	return { equipment, result };
}

void Forge::MakeEquipment()
{

}

void Forge::DisplayEquipmentRecipe()
{
	cout << "아래에 있는 재료를 통해 멋진 장비를 제작할 수 있습니다." << endl;
}

void Forge::AddEquipmentRecipe()
{

}