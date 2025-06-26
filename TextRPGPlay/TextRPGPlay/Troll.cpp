#include "Monster.h"
#include "Troll.h"
#include "ItemManager.h"
#include <vector>

Troll::Troll(int level) {
	name = "Troll";
	dropItem = ItemManager::Get().CreateItem("Æ®·Ñ°¡Á×");
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