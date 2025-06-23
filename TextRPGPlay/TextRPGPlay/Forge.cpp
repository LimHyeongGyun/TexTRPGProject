#include <iostream>

#include "Forge.h"
#include "item.h"
#include "Inventory.h"
#include "Character.h"
#include "ItemManager.h"

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
			cout << "����� �������� ��ī����: ���͸� ������ ��� �����Ϸ� ����!" << endl;
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
			EquipmentRecipe* findRecipe = nullptr;
			for (EquipmentRecipe& recipe : recipeBook)
			{
				if (recipe.craftEquipment->GetName() == "�巡�� �̻���")
				{
					findRecipe = &recipe;
					break;
				}
			}
			
			bool hasToken = false;
			hasToken = true;

			bool usedDragonPart = false;
			if (hasToken)
			{
				for (unordered_map<Item*, int>::value_type& token : Inventory::Get()->otherItems)
				{
					for (unordered_map<string, int>::value_type& heart : findRecipe->materials)
					{
						//�巡���� ��Ƽ� ���� ��ᰡ ������
						if (heart.first == token.first->GetName())
						{
							Craft(*findRecipe, findRecipe->craftEquipment);
							usedDragonPart = true;
							break;
						}
					}
					if (usedDragonPart)
					{
						break;
					}
				}
				if (!usedDragonPart)
				{
					cout << "����� �������� ��ī����: ������ ���� �巡���� �λ깰�� �� ����� �� ������?" << endl;
					cout << "����� �������� ��ī����: �� ����� ������ �巡�� �Ѹ��� �� ��ƺ����!" << endl;
				}
			}

			//�巡���� ���� ��ǥ�� ������
			if (!hasToken)
			{
				cout << "����� �������� ��ī����: �̰� ���� �� ���� �ּ��̰� ����� �� �ִ°� �ƴϾ�!" << endl;
				cout << "����� �������� ��ī����: �巡�� ������ ��� �����!" << endl;
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
	cout << "��ȭ�� ���ī�װ� ��ȣ�� �Է����ּ���.[1.����, 2.��]: " << endl;
	cin >> category;

	vector<Item*> itemList; //��� �κ��丮�� ������ ����

	switch (category)
	{
		case 1:
			itemList = Inventory::Get()->weaponItems;
			cout << "���� ������ ��ȭ ������ ���� ����Ʈ" << endl;
			break;
		case 2:
			itemList = Inventory::Get()->armorItems;
			cout << "���� ������ ��ȭ ������ �� ����Ʈ" << endl;
			break;
		default:
			cout << "�߸��� ��ȣ�Դϴ�." << endl;
			return;
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
			cout << "�ٽ� �Է��� �ּ���" << endl;
			system("pause");
		}
	}
	
	//���
	pair<Item*, string> result = Upgrade(itemList[selected - 1]);

	cout << result.first->GetName() << "�� ��ȭ��" << result.second << "�߽��ϴ�." << endl;
	
	//��ȭ�� �������� ��
	if (result.second == "����") {
		cout << "��ȭ �ܰ�: " << result.first->GetUpgradePhase() - 1 << "=>" << result.first->GetUpgradePhase() << endl;
		if (result.first->GetType() == ItemType::Weapon)
		{
			cout << "��ȭ �� ������ ��ġ" << result.first->GetAtack() - upgradeAtkValue << "=>" << result.first->GetAtack() << endl;
		}
		else if (result.first->GetType() == ItemType::Armor)
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
	int successRate = UpgradePercent(equipment->GetUpgradePhase());
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

vector<Forge::EquipmentRecipe> Forge::CanCraftRecipes()
{
	vector<EquipmentRecipe>craftableList;

	for (const EquipmentRecipe& recipe : recipeBook)
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
				if (pair.first->GetName() == name && pair.second >= requiredAmount)
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
	for(int i = 0; i < recipeBook.size(); i++)
	{
		cout << i + 1 << "." << recipeBook[i].craftEquipment->GetName() << "�ʿ��� ���: [";
		for(const unordered_map<string, int>::value_type& pair : recipeBook[i].materials)
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

	vector<EquipmentRecipe> craftableList = CanCraftRecipes();
	
	if(craftableList.empty())
	{
		cout << "���� ���� ������ ��� �����ϴ�." << endl;
		return;
	}
	for (int i = 0; i < craftableList.size(); i++)
	{
		cout << i+1 << "." << craftableList[i].craftEquipment->GetName()
			<< "���ݷ�: " << craftableList[i].craftEquipment->GetAtack()
			<< "ü��: " << craftableList[i].craftEquipment->GetBonusHealth() << endl;
	}

	int num;
	cout << "������ ���������� ��ȣ�� �Է����ּ���: ";
	cin >> num;

	Craft(craftableList[num - 1], craftableList[num - 1].craftEquipment);
}

void Forge::Craft(const EquipmentRecipe& recipe, Item* item)
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

void Forge::InitRecipes()
{
	Item* softArmor = ItemManager::Get()->CreateItem("������ ��ȣ��");
	unordered_map<string, int> needMat = {{"�������� ��", 2}, {"����� �㸮��", 2}};
	AddCraftRecipe(softArmor, needMat);
}

void Forge::AddCraftRecipe(Item* craftItem, const unordered_map<string, int> materials)
{
	recipeBook.emplace_back(craftItem, materials);
}
#pragma endregion
