#include <iostream>

#include "Forge.h"
#include "item.h"
#include "Inventory.h"
#include "Character.h"

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
			CraftEquipment();
		}
		else if (num == 3)
		{
			DisplayAllRecipes();
		}
		else if (num == 4)
		{
			Item* test; //나중에 DB에서 끌어다주기
			unordered_map<Item*, int>::iterator dragonToken = Inventory::Get()->expendableItems.find(test);
			//드래곤을 잡은 증표가 없을때
			if (dragonToken == Inventory::Get()->expendableItems.end())
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
			itemList = Inventory::Get()->weaponItems;
			cout << "내가 소지한 무기 리스트" << endl;
			break;
		case 2:
			itemList = Inventory::Get()->armorItems;
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
		cout << "강화 단계: " << result.first->GetupgradePhase() - 1 << "=>" << result.first->GetupgradePhase() << endl;
		if (result.first->itemType == Weapon)
		{
			cout << "강화 후 아이템 수치" << result.first->GetAttackPower() - upgradeAtkValue << "=>" << result.first->GetAttackPower() << endl;
		}
		else if (result.first->itemType == Armor)
		{
			cout << "강화 후 아이템 수치" << result.first->GetBonusHealth() - upgradeHpValue << "=>" << result.first->GetBonusHealth() << endl;
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
	int successRate = UpgradePercent(equipment->GetupgradePhase());
	int roll = rand() % 100;

	if (roll < successRate)
	{
		result = "성공";
		/*equipment->upgradePhase++;
		if (equipment->itemType == Weapon) equipment->attackPower += upgradeAtkValue;
		else if (equipment->itemType == Armor) equipment->health += upgradeHpValue;*/
	}
	else
	{
		result = "실패";
	}

	return { equipment, result };
}

#pragma region CraftEquipment

vector<Forge::EquipmentRecipeDB> Forge::CanCraftRecipes()
{
	vector<EquipmentRecipeDB>craftableList;

	for (const EquipmentRecipeDB& recipe : recipeList)
	{
		bool canCraft = false;
		for (const unordered_map<string, int>::value_type& material : recipe.materials)
		{
			const string& name = material.first; //재료의 이름
			int requiredAmount = material.second; //재료의 수량

			bool found = false;
			for (unordered_map<Item*, int>::value_type& pair : Inventory::Get()->otherItems)
			{
				//이름이 일치하고 수량이 충분할 때
				if (pair.first->name == name && pair.second >= requiredAmount)
				{
					found = true;
					break;
				}
			}

			//이름에 맞는 아이템이 없거나 수량이 부족하면
			if (!found)
			{
				canCraft = false;
				break;
			}
		}
		if (canCraft)
		{
			craftableList.push_back(recipe);
		}
	}

	return craftableList;
}

void Forge::DisplayAllRecipes()
{
	for(int i = 0; i < recipeList.size(); i++)
	{
		cout << i + 1 << "." << recipeList[i].equipment->name << "필요한 재료: [";
		for(const unordered_map<string, int>::value_type& pair : recipeList[i].materials)
		{
			cout << pair.first << " " << pair.second << "개";
		}
		cout << "]" << endl;
	}
}

void Forge::CraftEquipment()
{
	cout << "대장간에서는 멋진 장비를 제작할 수 있습니다!" << endl;
	cout << "현재 제작 가능한 아이템 목록" << endl;

	vector<EquipmentRecipeDB> craftableList = CanCraftRecipes();
	
	if(craftableList.empty())
	{
		cout << "현재 제작 가능한 장비가 없습니다." << endl;
		return;
	}
	for (int i = 0; i < craftableList.size(); i++)
	{
		cout << i+1 << "." << craftableList[i].equipment->name 
			<< "공격력: " << craftableList[i].equipment->GetAttackPower() 
			<< "체력: " << craftableList[i].equipment->GetBonusHealth() << endl;
	}

	int num;
	cout << "제작할 장비아이템의 번호를 입력해주세요: ";
	cin >> num;

	Craft(craftableList[num - 1], craftableList[num - 1].equipment);
}

void Forge::Craft(const EquipmentRecipeDB& recipe, Item* item)
{
	//Inventory에 제거할 재료목록 전달
	unordered_map<string, int> materialMap = recipe.materials;
	Inventory::Get()->RemoveItem(materialMap);

	//Character에 제작한 아이템 전달
	cout << "아이템 제작에 성공했습니다!" << endl;
	vector<Item*> _item;
	_item.push_back(item);
	Character::Get()->GetItem(_item);

}

#pragma endregion

#pragma region RecipeManagement
void Forge::AddEquipmentRecipe(Item* equipment, unordered_map<string, int> materials)
{

}
#pragma endregion

