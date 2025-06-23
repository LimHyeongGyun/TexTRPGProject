#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <array>

class Item;

class Forge {
private:
	struct EquipmentRecipe{
		Item* craftEquipment;
		std::unordered_map<std::string, int> materials;

		EquipmentRecipe(Item* craftEquip, std::unordered_map<std::string, int> craftMats)
			: craftEquipment(craftEquip), materials(craftMats){ }
	};
	//��ȭ Ȯ��
	struct UpgradeProbablity {
		int maxPer = 100;
		std::array<int, 9> per = { 100, 90, 80, 70, 60, 50, 30, 20, 10 };
	};
	std::vector<EquipmentRecipe> recipeBook; //��� ������DB
	UpgradeProbablity UP; //��ȭȮ��
	int expense = 0; //Forge���� ����ϴ� �۾��� ��� ���

	std::pair<Item*, std::string> Upgrade(Item* equipment); //��� ��ȭ
	int UpgradePercent(int upValue); //��ȭ Ȯ��
	void DisplayUpgradeEquipment(); //��ȭ ������ ��� �����ֱ�

	void DisplayAllRecipes(); //��� ��� ������ �����ֱ�
	void CraftEquipment(); //��� �����ϱ�
	std::vector<EquipmentRecipe> CanCraftRecipes(); //���� ������ ������ ��ȯ
	void Craft(const EquipmentRecipe& recipe, Item* item); //��� ����

	void InitRecipes();
	void AddCraftRecipe(Item* equipment, std::unordered_map<std::string, int> materials);//���ս� �߰�

public:
	int upgradeAtkValue = 0; //��ȭ�� ��� ���ݷ�
	int upgradeHpValue = 0; //��ȭ�� ��� ü��
	void EnteredForge(); //Forge�� ����
};