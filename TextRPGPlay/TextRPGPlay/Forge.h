#pragma once

#include <string>
#include <vector>

class Item;

class Forge {
private:
	struct EquipmentRecipeDB {
		Item* equipment;
	};

	int expense; //Forge에서 사용하는 작업에 드는 비용
	std::pair<Item*, std::string> Upgrade(Item* equipment);
	std::vector<EquipmentRecipeDB> recipeList; //장비 레시피 리스트

	void DisplayUpgradeEquipment(); //장비 강화
	void MakeEquipment(); //장비 제작
	void DisplayEquipmentRecipe(); //장비 조합식 확인
	void AddEquipmentRecipe();
public:
	void EnteredForge(); //Forge에 입장
};