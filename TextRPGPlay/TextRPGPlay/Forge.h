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
	//강화 확률
	struct UpgradeProbablity {
		int maxPer = 100;
		std::array<int, 9> per = { 100, 90, 80, 70, 60, 50, 30, 20, 10 };
	};
	std::vector<EquipmentRecipe> recipeBook; //장비 레시피DB
	UpgradeProbablity UP; //강화확률
	int expense = 0; //Forge에서 사용하는 작업에 드는 비용

	void JudgementUseUniqueCategory(); //카테고리 사용할 수 있는지 판단

	//강화
	int upgradeAtkValue;
	int upgradeHPValue;
	void Upgrade(Item* equipment); //장비 강화
	void DisplayUpgradePercent(); //강화확률 보여주기
	int GetUpgradePercent(int upValue); //강화 확률
	void DisplayPossibleUpgradEquipment(); //강화 가능한 장비 보여주기

	//장비 제작
	void CraftCategory(); //제작 카테고리
	std::vector<EquipmentRecipe> CanCraftRecipes(); //제작 가능한 레시피 반환
	void Craft(const EquipmentRecipe& recipe, Item* item); //장비 제작
	void CraftUniqueEquipiment(std::string recipeName); //유니크 아이템 제작

	//레시피
	void DisplayAllRecipes(); //모든 장비 레시피 보여주기
	void CreateRecipe();
	void InitRecipes(Item* craftItem, std::unordered_map<std::string, int> mats); //레시피 생성
	void AddCraftRecipe(Item* equipment, std::unordered_map<std::string, int> materials);//레시피 추가
	EquipmentRecipe* FindRecipe(std::string recipeName); //레시피 찾기

public:
	int GetUpgradeAtkValue(); //강화로 얻는 공격력
	int GetUpgradeHPValue(); //강화로 얻는 체력
	void UpgradeResult(Item* equipment, int percent, int successRate);
	void EnteredForge(); //Forge에 입장
};