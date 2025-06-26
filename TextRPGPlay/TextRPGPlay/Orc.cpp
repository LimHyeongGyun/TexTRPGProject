#include "ItemManager.h"
#include "Monster.h"
#include "Orc.h"

Orc::Orc(int level) {
	name = "Orc";
	dropItem = ItemManager::Get().CreateItem(rollRandomItem());
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