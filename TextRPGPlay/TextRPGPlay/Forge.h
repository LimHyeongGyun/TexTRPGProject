#pragma once

#include <string>
#include <vector>
#include <array>

class Item;

class Forge {
private:
	struct EquipmentRecipeDB {
		Item* equipment;
	};
	std::vector<EquipmentRecipeDB> recipeList; //��� ������ ����Ʈ
	//��ȭ Ȯ��
	struct UpgradeProbablity {
		int maxPer = 100;
		std::array<int, 9> per = { 100, 90, 80, 70, 60, 50, 30, 20, 10 };
	};
	UpgradeProbablity UP; //��ȭȮ��

	int expense; //Forge���� ����ϴ� �۾��� ��� ���

	std::pair<Item*, std::string> Upgrade(Item* equipment); //��� ��ȭ
	int UpgradePercent(int upValue); //��ȭ Ȯ��
	void DisplayUpgradeEquipment(); //��ȭ ������ ��� �����ֱ�
	void MakeEquipment(); //��� ����
	void DisplayEquipmentRecipe(); //��� ���ս� Ȯ��
	void AddEquipmentRecipe();//���ս� �߰�
public:
	void EnteredForge(); //Forge�� ����
};