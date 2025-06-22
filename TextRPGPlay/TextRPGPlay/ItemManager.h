#pragma once
#include <map>
#include <memory>
#include <string>
#include "Item.h"

class ItemManager
{
private:
	std::map < std::string, std::unique_ptr<Item>> prototypes;
	ItemManager();
	~ItemManager();


public:
		static ItemManager& GetInstance();

	ItemManager(const ItemManager&) = delete;
	void operator=(const ItemManager&) = delete;

	Item* CreateItem(const std::string& name);

};

