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
	std::vector<EquipmentRecipeDB> recipeList; //장비 레시피 리스트
	//강화 확률
	struct UpgradeProbablity {
		int maxPer = 100;
		std::array<int, 9> per = { 100, 90, 80, 70, 60, 50, 30, 20, 10 };
	};
	UpgradeProbablity UP; //강화확률

	int expense; //Forge에서 사용하는 작업에 드는 비용

	std::pair<Item*, std::string> Upgrade(Item* equipment); //장비 강화
	int UpgradePercent(int upValue); //강화 확률
	void DisplayUpgradeEquipment(); //강화 가능한 장비 보여주기
	void MakeEquipment(); //장비 제작
	void DisplayEquipmentRecipe(); //장비 조합식 확인
	void AddEquipmentRecipe();//조합식 추가
public:
	void EnteredForge(); //Forge에 입장
};