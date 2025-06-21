#pragma once

#include <string>
#include <vector>

class Item;

class Forge {
private:
	struct EquipmentRecipeDB {
		Item* equipment;
	};

	int expense; //Forge���� ����ϴ� �۾��� ��� ���
	std::pair<Item*, std::string> Upgrade(Item* equipment);
	std::vector<EquipmentRecipeDB> recipeList; //��� ������ ����Ʈ

	void DisplayUpgradeEquipment(); //��� ��ȭ
	void MakeEquipment(); //��� ����
	void DisplayEquipmentRecipe(); //��� ���ս� Ȯ��
	void AddEquipmentRecipe();
public:
	void EnteredForge(); //Forge�� ����
};