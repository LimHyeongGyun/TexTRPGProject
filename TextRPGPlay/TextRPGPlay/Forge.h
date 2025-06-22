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
	//강화 확률
	struct UpgradeProbablity {
		int maxPer = 100;
		std::array<int, 9> per = { 100, 90, 80, 70, 60, 50, 30, 20, 10 };
	};
	std::vector<EquipmentRecipeDB> recipeList; //장비 레시피 리스트
	UpgradeProbablity UP; //강화확률
	int expense = 0; //Forge에서 사용하는 작업에 드는 비용

	std::pair<Item*, std::string> Upgrade(Item* equipment); //장비 강화
	int UpgradePercent(int upValue); //강화 확률
	void DisplayUpgradeEquipment(); //강화 가능한 장비 보여주기

	void DisplayAllRecipes(); //모든 장비 레시피 보여주기
	void CraftEquipment(); //장비 제작하기
	std::vector<EquipmentRecipeDB> CanCraftRecipes(); //제작 가능한 레시피 반환
	void Craft(const EquipmentRecipeDB& recipe, Item* item); //장비 제작

	void AddEquipmentRecipe(Item* equipment, std::unordered_map<std::string, int> materials);//조합식 추가

public:
	int upgradeAtkValue = 0; //강화로 얻는 공격력
	int upgradeHpValue = 0; //강화로 얻는 체력
	void EnteredForge(); //Forge에 입장
};