#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <array>

class Item;

class Forge {
private:
	struct EquipmentRecipeDB {
		Item* equipment;
		std::unordered_map<std::string, int> materials;
	};
	//��ȭ Ȯ��
	struct UpgradeProbablity {
		int maxPer = 100;
		std::array<int, 9> per = { 100, 90, 80, 70, 60, 50, 30, 20, 10 };
	};
	std::vector<EquipmentRecipeDB> recipeList; //��� ������ ����Ʈ
	UpgradeProbablity UP; //��ȭȮ��
	int expense = 0; //Forge���� ����ϴ� �۾��� ��� ���

	std::pair<Item*, std::string> Upgrade(Item* equipment); //��� ��ȭ
	int UpgradePercent(int upValue); //��ȭ Ȯ��
	void DisplayUpgradeEquipment(); //��ȭ ������ ��� �����ֱ�

	void DisplayAllRecipes(); //��� ��� ������ �����ֱ�
	void CraftEquipment(); //��� �����ϱ�
	std::vector<EquipmentRecipeDB> CanCraftRecipes(); //���� ������ ������ ��ȯ
	void Craft(const EquipmentRecipeDB& recipe, Item* item); //��� ����

	void AddEquipmentRecipe(Item* equipment, std::unordered_map<std::string, int> materials);//���ս� �߰�

public:
	int upgradeAtkValue = 0; //��ȭ�� ��� ���ݷ�
	int upgradeHpValue = 0; //��ȭ�� ��� ü��
	void EnteredForge(); //Forge�� ����
};