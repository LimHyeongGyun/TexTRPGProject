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

	void JudgementUseUniqueCategory(); //ī�װ� ����� �� �ִ��� �Ǵ�

	//��ȭ
	int upgradeAtkValue;
	int upgradeHPValue;
	void Upgrade(Item* equipment); //��� ��ȭ
	void DisplayUpgradePercent(); //��ȭȮ�� �����ֱ�
	int GetUpgradePercent(int upValue); //��ȭ Ȯ��
	void DisplayPossibleUpgradEquipment(); //��ȭ ������ ��� �����ֱ�

	//��� ����
	void CraftCategory(); //���� ī�װ�
	std::vector<EquipmentRecipe> CanCraftRecipes(); //���� ������ ������ ��ȯ
	void Craft(const EquipmentRecipe& recipe, Item* item); //��� ����
	void CraftUniqueEquipiment(std::string recipeName); //����ũ ������ ����

	//������
	void DisplayAllRecipes(); //��� ��� ������ �����ֱ�
	void CreateRecipe();
	void InitRecipes(Item* craftItem, std::unordered_map<std::string, int> mats); //������ ����
	void AddCraftRecipe(Item* equipment, std::unordered_map<std::string, int> materials);//������ �߰�
	EquipmentRecipe* FindRecipe(std::string recipeName); //������ ã��

public:
	int GetUpgradeAtkValue(); //��ȭ�� ��� ���ݷ�
	int GetUpgradeHPValue(); //��ȭ�� ��� ü��
	void UpgradeResult(Item* equipment, int percent, int successRate);
	void EnteredForge(); //Forge�� ����
};