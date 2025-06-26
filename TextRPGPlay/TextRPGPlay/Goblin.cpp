#include <vector>
#include "ItemManager.h"
#include "Monster.h"
#include "Goblin.h"

Goblin::Goblin(int level) {
	name = "Goblin";
	dropItem = ItemManager::Get().CreateItem("∞Ì∫Ì∏∞¿Ãª°");
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