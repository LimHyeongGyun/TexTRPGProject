#include "Monster.h"
#include "Slime.h"
#include "ItemManager.h"
#include <vector>

Slime::Slime(int level) {
	name = "Slime";
	dropItem = ItemManager::Get().CreateItem("끈적한점액");
	alive = true;

	int baseMinHp = level * 20;
	int baseMaxHp = level * 30;

	int baseMinAtk = level * 5;
	int baseMaxAtk = level * 10;

	health = getRandomInRange(baseMinHp, baseMaxHp) * getMultiplyHp();
	attack = getRandomInRange(baseMinAtk, baseMaxAtk) * getMultiplyAtk();

	expDrop = 50;
	goldDrop = getRandomInRange(10, 20);

	ItemDrop();
}