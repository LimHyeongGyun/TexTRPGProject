#include <iostream>
#include "Forge.h"
#include "item.h"
#include "Inventory.h"

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
			MakeEquipment();
		}
		else if (num == 3)
		{
			DisplayEquipmentRecipe();
		}
		else if (num == 4)
		{
			Item* test; //���߿� DB���� ������ֱ�
			unordered_map<Item*, int>::iterator dragonToken = Inventory::Get()->consumableValue.find(test);
			//�巡���� ���� ��ǥ�� ������
			if (dragonToken == Inventory::Get()->consumableValue.end())
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
			itemList = Inventory::Get()->weaponValue;
			cout << "���� ������ ���� ����Ʈ" << endl;
			break;
		case2:
			itemList = Inventory::Get()->armorValue;
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
		cout << "��ȭ �ܰ�: " << result.first->upgradePhase - 1 << "=>" << result.first->upgradePhase << endl;
		if (result.first->itemType == Weapon)
		{
			cout << "��ȭ �� ������ ��ġ" << result.first->attack - result.first->upgradeAtkValue << "=>" << result.first->attack << endl;
		}
		else if (result.first->itemType == Armor)
		{
			cout << "��ȭ �� ������ ��ġ" << result.first->health - result.first->upgradeHpValue << "=>" << result.first->health << endl;
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
	int successRate = UpgradePercent(equipment->upgradePhase);
	int roll = rand() % 100;

	if (roll < successRate)
	{
		result = "����";
		equipment->upgradePhase++;
		if (equipment->itemType == Weapon) equipment->attack += equipment->upgradeAtkValue;
		else if (equipment->itemType == Armor) equipment->health += equipment->upgradeHpValue;
	}
	else
	{
		result = "����";
	}

	return { equipment, result };
}

void Forge::MakeEquipment()
{

}

void Forge::DisplayEquipmentRecipe()
{
	cout << "�Ʒ��� �ִ� ��Ḧ ���� ���� ��� ������ �� �ֽ��ϴ�." << endl;
}

void Forge::AddEquipmentRecipe()
{

}