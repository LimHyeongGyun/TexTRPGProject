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
	int num;

	cin.ignore();
	cout << "����� �������� ��ī����: ���� ������ �־ �Գ�?" << endl;

	while (true)
	{
		cout << "0.���尣 ������" << endl;
		cout << "1.���ȭ" << endl;
		cout << "2.������� " << endl;
		cout << "3.���ս� Ȯ���ϱ�" << endl;
		cout << "4.����ũ ������ ����" << endl;
		cout << "������ �۾��� ��ȣ�� �Է����ּ���: ";
		cin >> num;

		switch (num)
		{
			case 0:
				cout << "����� �������� ��ī����: ���͸� ������ ��� �����Ϸ� ����!" << endl;
				cout << "����� �������� ��ī����: ���� ���� ���� ���� ���������!" << endl;
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
				JudgementUseCategory();
				break;
			default:
				cout << GameManager::Get().WrongInputMessage();
				continue;
		}

		break;
	}
}

void Forge::JudgementUseCategory()
{
	for (unordered_map<Item*, int>::value_type& token : Inventory::Get().otherItems)
	{
		if (token.first->GetName() == "�巡�� ��ǥ") //���߿� ��ǥ ��ū�� ���� �ؼ� ����
		{
			//���� ���� ������ CraftUniqueItem�� �����ϰ� ���۰����� ����ũ������ ��� �����ֱ�
			CraftUniqueEquipiment("�巡�� �̻���");
			return;
		}
	}

	//Ư���� ���͸� ���� ��ǥ�� ������
	cout << "����� �������� ��ī����: �̰� ���� �� ���� �ּ��̰� ����� �� �ִ°� �ƴϾ�!" << endl;
	cout << "����� �������� ��ī����: �巡�� ������ ��� �����!" << endl;
}
void Forge::DisplayPossibleUpgradEquipment()
{
	DisplayUpgradePercent();

	int category = 0;
	vector<Item*> itemList; //��� �κ��丮�� ������ ����

	while (true)
	{
		cout << "��ȭ�� ���ī�װ� ��ȣ�� �Է����ּ���.[1.����, 2.��]: " << endl;
		cin >> category;

		switch (category)
		{
		case 1:
			itemList = Inventory::Get().weaponItems;
			cout << "���� ������ ��ȭ ������ ���� ����Ʈ" << endl;
			break;
		case 2:
			itemList = Inventory::Get().armorItems;
			cout << "���� ������ ��ȭ ������ �� ����Ʈ" << endl;
			break;
		default:
			cout << GameManager::Get().WrongInputMessage();;
			continue;
		}
		break;
	}

	if (!itemList.empty())
	{
		//�ִ�� ��ȭ�� ������ �����ϱ�
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

	//��ȭ�� ��� ������
	if (itemList.empty()) {
		cout << "��ȭ�� �� �ִ� ��� �����ϴ�." << endl;
		return;
	}

	//��� ����Ʈ ���
	for (int i = 0; i < itemList.size(); i++) {
		cout << i + 1 << "." << itemList[i]->GetName() << endl;
	}

	int selected = 0; //��� ����
	while (true)
	{
		cout << "��ȭ�� ������ ����� ��ȣ�� �Է����ּ���: ";
		cin >> selected;

		//��ȿ�� �˻�
		if (selected <= 0 || selected > static_cast<int>(itemList.size()))
		{
			cout << GameManager::Get().WrongInputMessage();
			system("pause");
		}
	}
	
	//���
	Upgrade(itemList[selected - 1]);
}

void Forge::DisplayUpgradePercent()
{
	cout << "==============��ȭȮ��==============" << endl;
	for (int i = 0; i < UP.per.size(); i++)
	{
		cout << i << "��ȭȮ��:" << UP.per[i] << endl;
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
	//��ȭ ����
	if (roll < successRate)
	{
		equipment->Upgrade(*this);

		cout << "��ȭ �ܰ�: " << equipment->GetUpgradePhase() - 1 << "=>" << equipment->GetUpgradePhase() << endl;
		if (equipment->GetType() == ItemType::Weapon)
		{
			cout << "��ȭ �� ������ ��ġ" << equipment->GetAttack() - GetUpgradeAtkValue() << "=>" << equipment->GetAttack() << endl;
		}
		else if (equipment->GetType() == ItemType::Armor)
		{
			cout << "��ȭ �� ������ ��ġ" << equipment->GetBonusHealth() - GetUpgradeAtkValue() << "=>" << equipment->GetBonusHealth() << endl;
		}
	}
	//��ȭ ����
	else
	{
		cout << "��ȭ�� �����߽��ϴ�. " << endl;
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
				//�̸��� ��ġ�ϰ� ������ ����� ��
				if (pair.first->GetName() == material.first && pair.second >= material.second)
				{
					found = true;
					break;
				}
			}

			//�̸��� �´� �������� ���ų� ������ �����ϸ�
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
	cout << "���尣������ ���� ��� ������ �� �ֽ��ϴ�!" << endl;
	cout << "���� ���� ������ ������ ���" << endl;
	vector<EquipmentRecipe> craftableList = CanCraftRecipes();
	
	if(craftableList.empty())
	{
		cout << "���� ���� ������ ��� �����ϴ�." << endl;
		return;
	}
	for (int i = 0; i < craftableList.size(); i++)
	{
		cout << i+1 << "." << craftableList[i].craftEquipment->GetName()
			<< "���ݷ�: " << craftableList[i].craftEquipment->GetAttack()
			<< "ü��: " << craftableList[i].craftEquipment->GetBonusHealth() << endl;
	}

	int num;
	while (true)
	{
		cout << "������ ���������� ��ȣ�� �Է����ּ���: ";
		cin >> num;

		if (num <= 0 || num > static_cast<int>(craftableList.size()))
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
	//�巡�� ���� ���� �� �ִ� ��� ã�ƿ���
	EquipmentRecipe* findRecipe = FindRecipe(recipeName);

	bool usedDragonPart = false;
	for (unordered_map<Item*, int>::value_type& bone : Inventory::Get().otherItems)
	{
		for (unordered_map<string, int>::value_type& mat : findRecipe->materials)
		{
			//�巡���� ��Ƽ� ���� ��ᰡ ������
			if (mat.first == bone.first->GetName())
			{
				Craft(*findRecipe, findRecipe->craftEquipment);
				usedDragonPart = true;
				return;
			}
		}
	}

	cout << "����� �������� ��ī����: ������ ���� �巡���� �λ깰�� �� ����� �� ������?" << endl;
	cout << "����� �������� ��ī����: �� ����� ������ �巡�� �Ѹ��� �� ��ƺ����!" << endl;
}

void Forge::Craft(const EquipmentRecipe& recipe, Item* item)
{
	//Inventory�� ������ ����� ����
	unordered_map<string, int> materialMap = recipe.materials;
	Inventory::Get().RemoveItem(materialMap);

	//Character�� ������ ������ ����
	cout << "������ ���ۿ� �����߽��ϴ�!" << endl;
	vector<Item*> _item;
	_item.push_back(item);
	Character::Get().GetItem(_item);

}
#pragma endregion

#pragma region RecipeManagement

void Forge::InitRecipes()
{
	Item* softArmor = ItemManager::Get().CreateItem("������ ��ȣ��");
	unordered_map<string, int> needMat = {{"�������� ��", 2}, {"����� �㸮��", 2}};
	AddCraftRecipe(softArmor, needMat);
}

void Forge::AddCraftRecipe(Item* craftItem, const unordered_map<string, int> materials)
{
	recipeBook.emplace_back(craftItem, materials);
}

void Forge::DisplayAllRecipes()
{
	for (int i = 0; i < recipeBook.size(); i++)
	{
		cout << i + 1 << "." << recipeBook[i].craftEquipment->GetName() << "�ʿ��� ���: ";
		for (const unordered_map<string, int>::value_type& pair : recipeBook[i].materials)
		{
			cout << "["  << pair.first << " " << pair.second << "��] ";
		}
	}
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
