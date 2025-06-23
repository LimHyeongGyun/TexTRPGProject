#pragma once
#include <map>
#include<string>
#include<memory>
#include"Item.h"

class ItemManager
{
private:
	std::map<std::string, std::unique_ptr<Item>> Itemdb;
	
	//싱글톤 패턴 구현
	ItemManager();
	~ItemManager();

public:
	static ItemManager& GetInstance();
	//싱글톤 패턴 객체를 생성하는 함수

	ItemManager(const ItemManager&) = delete;
	//복사 생성 차단

	ItemManager& operator=(const ItemManager&) = delete;
	//복사 차단

	Item* CreateItem(const std::string& name);
	//db로 부터 아이템 생성
};

