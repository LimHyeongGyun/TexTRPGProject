#include "Monster.h"
#include "Dragon.h"
#include "ItemManager.h"
#include <vector>

Dragon::Dragon(int level) {
	name = "Dragon";
	dropItem = ItemManager::Get().CreateItem("�巡�����");
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
