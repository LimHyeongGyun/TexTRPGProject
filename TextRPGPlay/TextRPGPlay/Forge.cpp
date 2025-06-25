#include <iostream>

#include "Forge.h"
#include "item.h"
#include "Inventory.h"
#include "Character.h"
#include "ItemManager.h"
#include "GameManager.h"

using namespace std;

void Forge::EnteredForge()
{
	CreateRecipe();
	int num;

	cout << "드워프 대장장이 불카누스: 무슨 볼일이 있어서 왔나?" << endl;

	while (true)
	{
		cout << "0.대장간 떠나기" << endl;
		cout << "1.장비강화" << endl;
		cout << "2.장비제작" << endl;
		cout << "3.조합식 확인하기" << endl;
		cout << "4.유니크 아이템 제작" << endl;
		cout << "진행할 작업의 번호를 입력해주세요: ";

		cin >> num;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore();
			cout << GameManager::Get().WrongInputMessage();;
			continue;
		}
		switch (num)
		{
			case 0:
				cout << "드워프 대장장이 불카누스: 몬스터를 잡으면 장비를 제작하러 오게!" << endl;
				cout << "드워프 대장장이 불카누스: 내가 아주 멋진 것을 만들어주지!" << endl;
				return;
			case 1:
				DisplayPossibleUpgradEquipment();
				break;
			case 2:
				CraftCategory();
				break;
			case 3:
				DisplayAllRecipes();
				break;
			case 4:
				JudgementUseUniqueCategory();
				break;
			default:
				cout << GameManager::Get().WrongInputMessage();
				break;
		}
	}
}

void Forge::JudgementUseUniqueCategory()
{
	for (unordered_map<Item*, int>::value_type& token : Inventory::Get().otherItems)
	{
		if (token.first->GetName() == "드래곤 증표") //나중에 증표 토큰은 따로 해서 변경
		{
			cout << "드워프 대장장이 불카누스: 애송이인줄 알았더니 드래곤을 잡아올줄이야!" << endl;
			cout << "드워프 대장장이 불카누스: 조금만 기다려봐 내가 걸작을 만들어주지!" << endl;
			//추후 여유 있을시 CraftUniqueItem을 제외하고 제작가능한 유니크아이템 목록 보여주기
			CraftUniqueEquipiment("용기사의창");
			return;
		}
	}

	//특별한 몬스터를 잡은 증표가 없을때
	cout << "드워프 대장장이 불카누스: 이건 아직 너 같은 애송이가 사용할 수 있는게 아니야!" << endl;
	cout << "드워프 대장장이 불카누스: 드래곤 정도는 잡고 오라고!" << endl;
}
void Forge::DisplayPossibleUpgradEquipment()
{
	DisplayUpgradePercent();

	int category = 0;
	vector<Item*> itemList; //장비 인벤토리를 저장할 변수

	while (true)
	{
		cout << "강화할 장비카테고리 번호를 입력해주세요.[0.강화취소 1.무기, 2.방어구]: " << endl;
		
		cin >> category;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore();
			cout << GameManager::Get().WrongInputMessage();;
			continue;
		}
		switch (category)
		{
		case 0:
			return;
		case 1:
			itemList = Inventory::Get().weaponItems;
			cout << "내가 소지한 강화 가능한 무기 리스트" << endl;
			break;
		case 2:
			itemList = Inventory::Get().armorItems;
			cout << "내가 소지한 강화 가능한 방어구 리스트" << endl;
			break;
		default:
			cout << GameManager::Get().WrongInputMessage();;
			break;
		}
		break;
	}

	if (!itemList.empty())
	{
		//최대로 강화된 아이템 제외하기
		for (vector<Item*>::iterator item = itemList.begin(); item != itemList.end();)
		{
			if ((*item)->GetUpgradePhase() == (*item)->GetMaxUpgradePhase())
			{
				itemList.erase(item);
			}
			else
			{
				++item;
			}
		}
	}

	//강화할 장비가 없을때
	if (itemList.empty()) {
		cout << "강화할 수 있는 장비가 없습니다." << endl;
		return;
	}

	//장비 리스트 출력
	for (int i = 0; i < itemList.size(); i++) {
		cout << i + 1 << "." << itemList[i]->GetName() << endl;
	}

	int selected = 0; //장비 순서
	while (true)
	{
		cout << "강화를 진행할 장비의 번호를 입력해주세요[0:취소]: ";

		if (cin.fail())
		{
			cin.clear();
			cin.ignore();
			cout << GameManager::Get().WrongInputMessage();;
			continue;
		}
		cin >> selected;
		if (selected == 0)
		{
			return;
		}
		//유효성 검사
		if (selected < 0 || selected > static_cast<int>(itemList.size()))
		{
			cout << GameManager::Get().WrongInputMessage();
			system("pause");
		}
	}
	
	//결과
	Upgrade(itemList[selected - 1]);
}

void Forge::DisplayUpgradePercent()
{
	cout << "==============강화확률==============" << endl;
	for (int i = 0; i < UP.per.size(); i++)
	{
		cout << i << "강화확률:" << UP.per[i] << endl;
	}
}

int Forge::GetUpgradePercent(int upValue)
{
	return UP.per[upValue];
}

void Forge::Upgrade(Item* equipment)
{
	int successRate = GetUpgradePercent(equipment->GetUpgradePhase());
	int roll = rand() % 100;

	UpgradeResult(equipment, roll, successRate);
}

void Forge::UpgradeResult(Item* equipment, int roll, int successRate)
{
	//강화 성공
	if (roll < successRate)
	{
		equipment->Upgrade(*this);

		cout << "강화 단계: " << equipment->GetUpgradePhase() - 1 << "=>" << equipment->GetUpgradePhase() << endl;
		if (equipment->GetType() == ItemType::Weapon)
		{
			cout << "강화 후 아이템 수치" << equipment->GetAttack() - GetUpgradeAtkValue() << "=>" << equipment->GetAttack() << endl;
		}
		else if (equipment->GetType() == ItemType::Armor)
		{
			cout << "강화 후 아이템 수치" << equipment->GetBonusHealth() - GetUpgradeAtkValue() << "=>" << equipment->GetBonusHealth() << endl;
		}
	}
	//강화 실패
	else
	{
		cout << "강화에 실패했습니다. " << endl;
	}
}

int Forge::GetUpgradeAtkValue()
{
	return upgradeAtkValue;
}

int Forge::GetUpgradeHPValue()
{
	return upgradeHPValue;
}


#pragma region CraftEquipment

vector<Forge::EquipmentRecipe> Forge::CanCraftRecipes()
{
	vector<EquipmentRecipe>craftableList;

	for (const EquipmentRecipe& recipe : recipeBook)
	{
		bool canCraft = false;
		for (const unordered_map<string, int>::value_type& material : recipe.materials)
		{
			bool found = false;
			for (unordered_map<Item*, int>::value_type& pair : Inventory::Get().otherItems)
			{
				//이름이 일치하고 수량이 충분할 때
				if (pair.first->GetName() == material.first && pair.second >= material.second)
				{
					found = true;
					break;
				}
			}

			//이름에 맞는 아이템이 없거나 수량이 부족하면
			if (!found)
			{
				canCraft = false;
			}
		}
		if (canCraft)
		{
			craftableList.push_back(recipe);
		}
	}

	return craftableList;
}

void Forge::CraftCategory()
{
	cout << "대장간에서는 멋진 장비를 제작할 수 있습니다!" << endl;
	cout << "현재 제작 가능한 아이템 목록" << endl;
	vector<EquipmentRecipe> craftableList = CanCraftRecipes();
	
	if(craftableList.empty())
	{
		cout << "현재 제작 가능한 장비가 없습니다." << endl;
		return;
	}
	for (int i = 0; i < craftableList.size(); i++)
	{
		cout << i+1 << "." << craftableList[i].craftEquipment->GetName()
			<< "공격력: " << craftableList[i].craftEquipment->GetAttack()
			<< "체력: " << craftableList[i].craftEquipment->GetBonusHealth() << endl;
	}

	int num;
	while (true)
	{
		cout << "제작할 장비아이템의 번호를 입력해주세요(취소하기: 0): ";
		cin >> num;

		if (cin.fail())
		{
			cin.clear();
			cin.ignore();
			cout << GameManager::Get().WrongInputMessage();;
			continue;
		}
		if (num == 0)
		{
			cout << "취소했습니다." << endl;
			EnteredForge();
			return;
		}
		if (num < 0 || num > static_cast<int>(craftableList.size()))
		{
			cout << GameManager::Get().WrongInputMessage();
			continue;
		}

		break;
	}

	Craft(craftableList[num - 1], craftableList[num - 1].craftEquipment);
}

void Forge::CraftUniqueEquipiment(string recipeName)
{
	//드래곤 재료로 만들 수 있는 재료 찾아오기
	EquipmentRecipe* findRecipe = FindRecipe(recipeName);

	for (unordered_map<Item*, int>::value_type& bone : Inventory::Get().otherItems)
	{
		for (unordered_map<string, int>::value_type& mat : findRecipe->materials)
		{
			//드래곤을 잡아서 얻은 재료가 있을때
			if (mat.first == bone.first->GetName())
			{
				cout << "드워프 대장장이 불카누스: 아주 걸작이야! 잘 써보라고" << endl;
				cout << "드워프 대장장이 불카누스: 귀한 재료를 만져봤으니 특별히 A/S는 무료로 해주지" << endl;
				Craft(*findRecipe, findRecipe->craftEquipment);
				return;
			}
		}
	}

	cout << "드워프 대장장이 불카누스: 저번에 잡은 드래곤의 부산물은 다 사용한 것 같은데?" << endl;
	cout << "드워프 대장장이 불카누스: 더 만들고 싶으면 드래곤 한마리 더 잡아보라고!" << endl;
}

void Forge::Craft(const EquipmentRecipe& recipe, Item* item)
{
	//Inventory에 제거할 재료목록 전달
	unordered_map<string, int> materialMap = recipe.materials;
	Inventory::Get().RemoveNoneEquipItem(materialMap, ItemType::Other);

	//Character에 제작한 아이템 전달
	cout << "아이템 제작에 성공했습니다!" << endl;
	vector<Item*> _item;
	_item.push_back(item);
	Character::Get().GetItem(_item);
}
#pragma endregion

#pragma region RecipeManagement

void Forge::CreateRecipe()
{
	InitRecipes(ItemManager::Get().CreateItem("고블린톱니단검"), { {"고블린이빨", 3}, {"거친가죽조각", 1}, {"고블린의귀걸이", 1}});
	InitRecipes(ItemManager::Get().CreateItem("오크어금니도끼"), { {"오크의어금니", 2}, {"오크족전투휘장", 1} });
	InitRecipes(ItemManager::Get().CreateItem("오크가죽갑옷"), { {"상처난오크등가죽", 3}, {"오크등가죽", 2} });
	InitRecipes(ItemManager::Get().CreateItem("트롤뼈몽둥이"), { {"트롤의변이된 손톱", 3}, {"트롤의가죽", 1} });
	InitRecipes(ItemManager::Get().CreateItem("트롤가죽갑옷"), { {"트롤의가죽", 5}, {"트롤의재생혈액", 2} });
	InitRecipes(ItemManager::Get().CreateItem("용기사의창"), { {"드래곤의발톱", 1}, {"드래곤의비늘", 2} });
	InitRecipes(ItemManager::Get().CreateItem("용기사의갑주"), { {"드래곤심장", 1}, {"드래곤의비늘", 2} });
}
void Forge::InitRecipes(Item* craftItem, unordered_map<string, int> mats)
{
	AddCraftRecipe(craftItem, mats);
}

void Forge::AddCraftRecipe(Item* craftItem, const unordered_map<string, int> materials)
{
	recipeBook.emplace_back(craftItem, materials);
}

void Forge::DisplayAllRecipes()
{
	for (int i = 0; i < recipeBook.size(); i++)
	{
		cout << i + 1 << "." << recipeBook[i].craftEquipment->GetName() << " 필요한 재료: ";
		for (const unordered_map<string, int>::value_type& pair : recipeBook[i].materials)
		{
			cout << "["  << pair.first << " " << pair.second << "개] ";
		}
		cout << endl;
	}
	system("pause");
}

Forge::EquipmentRecipe* Forge::FindRecipe(std::string recipeName)
{
	for (EquipmentRecipe& recipe : recipeBook)
	{
		if (recipe.craftEquipment->GetName() == recipeName)
		{
			return &recipe;
		}
	}

	return nullptr;
}
#pragma endregion
