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
	cout << "����� �������� ��ī����: ���� ������ �־ �Գ�?" << endl;

	while (true)
	{
		cout << "0.���尣 ������" << endl;
		cout << "1.���ȭ" << endl;
		cout << "2.������� " << endl;
		cout << "3.���ս� Ȯ���ϱ�" << endl;
		cout << "4.???" << endl;
		cout << "������ �۾��� ��ȣ�� �Է����ּ���: ";
		cin >> num;

		if (num == 0)
		{
			cout << "����� �������� ��ī����: �巡���� ������ ��� �����Ϸ� ����!" << endl;
			cout << "����� �������� ��ī����: ���� ���� ���� ���� ���������!" << endl;
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
			Item* test; //���߿� DB���� ������ֱ�
			unordered_map<Item*, int>::iterator dragonToken = Inventory::Get()->expendableItems.find(test);
			//�巡���� ���� ��ǥ�� ������
			if (dragonToken == Inventory::Get()->expendableItems.end())
			{

			}
			//�巡���� ���� ��ǥ�� ������
			else
			{

			}
		}
		else
		{
			cout << "���� ������ �۾��� �Է����ּ���." << endl;
		}
	}
}

void Forge::DisplayUpgradeEquipment()
{
	cout << "==============��ȭȮ��==============" << endl;
	for (int i = 0; i < UP.per.size(); i++)
	{
		cout << i << "�� ��ȭȮ��:" << UP.per[i] << endl;
	}

	int category = 0;
	cout << "��ȭ�� ��� ��ȣ�� �Է����ּ���.[1.����, 2.��]: " << endl;
	cin >> category;

	vector<Item*> itemList; //��� �κ��丮�� ������ ����

	switch (category)
	{
		case 1:
			itemList = Inventory::Get()->weaponItems;
			cout << "���� ������ ���� ����Ʈ" << endl;
			break;
		case 2:
			itemList = Inventory::Get()->armorItems;
			cout << "���� ������ �� ����Ʈ" << endl;
			break;
		default:
			cout << "�߸��� ��ȣ�Դϴ�." << endl;
			return;
	}

	//��ȭ�� ��� ������
	if (itemList.empty()) {
		cout << "��ȭ�� �� �ִ� ��� �����ϴ�." << endl;
		return;
	}

	//��� ����Ʈ ���
	for (int i = 0; i < itemList.size(); i++) {
		cout << i + 1 << "." << itemList[i]->name << endl;
	}

	int selected = 0; //��� ����
	while (true)
	{
		cout << "��ȭ�� ������ ����� ��ȣ�� �Է����ּ���: ";
		cin >> selected;

		//��ȿ�� �˻�
		if (selected <= 0 || selected > static_cast<int>(itemList.size()))
		{
			cout << "�ٽ� �Է��� �ּ���" << endl;
			system("pause");
		}
	}
	
	//���
	pair<Item*, string> result = Upgrade(itemList[selected - 1]);

	cout << result.first->name << "�� ��ȭ��" << result.second << "�߽��ϴ�." << endl;
	
	//��ȭ�� �������� ��
	if (result.second == "����") {
		cout << "��ȭ �ܰ�: " << result.first->GetupgradePhase() - 1 << "=>" << result.first->GetupgradePhase() << endl;
		if (result.first->itemType == Weapon)
		{
			cout << "��ȭ �� ������ ��ġ" << result.first->GetAttackPower() - upgradeAtkValue << "=>" << result.first->GetAttackPower() << endl;
		}
		else if (result.first->itemType == Armor)
		{
			cout << "��ȭ �� ������ ��ġ" << result.first->GetBonusHealth() - upgradeHpValue << "=>" << result.first->GetBonusHealth() << endl;
		}
	}
	//��ȭ�� �������� ��
	else if (result.second == "����")
	{
		cout << "��ȭ�� �����߽��ϴ�. " << endl;
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
		result = "����";
		/*equipment->upgradePhase++;
		if (equipment->itemType == Weapon) equipment->attackPower += upgradeAtkValue;
		else if (equipment->itemType == Armor) equipment->health += upgradeHpValue;*/
	}
	else
	{
		result = "����";
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
			const string& name = material.first; //����� �̸�
			int requiredAmount = material.second; //����� ����

			bool found = false;
			for (unordered_map<Item*, int>::value_type& pair : Inventory::Get()->otherItems)
			{
				//�̸��� ��ġ�ϰ� ������ ����� ��
				if (pair.first->name == name && pair.second >= requiredAmount)
				{
					found = true;
					break;
				}
			}

			//�̸��� �´� �������� ���ų� ������ �����ϸ�
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
		cout << i + 1 << "." << recipeList[i].equipment->name << "�ʿ��� ���: [";
		for(const unordered_map<string, int>::value_type& pair : recipeList[i].materials)
		{
			cout << pair.first << " " << pair.second << "��";
		}
		cout << "]" << endl;
	}
}

void Forge::CraftEquipment()
{
	cout << "���尣������ ���� ��� ������ �� �ֽ��ϴ�!" << endl;
	cout << "���� ���� ������ ������ ���" << endl;

	vector<EquipmentRecipeDB> craftableList = CanCraftRecipes();
	
	if(craftableList.empty())
	{
		cout << "���� ���� ������ ��� �����ϴ�." << endl;
		return;
	}
	for (int i = 0; i < craftableList.size(); i++)
	{
		cout << i+1 << "." << craftableList[i].equipment->name 
			<< "���ݷ�: " << craftableList[i].equipment->GetAttackPower() 
			<< "ü��: " << craftableList[i].equipment->GetBonusHealth() << endl;
	}

	int num;
	cout << "������ ���������� ��ȣ�� �Է����ּ���: ";
	cin >> num;

	Craft(craftableList[num - 1], craftableList[num - 1].equipment);
}

void Forge::Craft(const EquipmentRecipeDB& recipe, Item* item)
{
	//Inventory�� ������ ����� ����
	unordered_map<string, int> materialMap = recipe.materials;
	Inventory::Get()->RemoveItem(materialMap);

	//Character�� ������ ������ ����
	cout << "������ ���ۿ� �����߽��ϴ�!" << endl;
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

