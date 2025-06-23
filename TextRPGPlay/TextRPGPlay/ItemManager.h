#pragma once
#include <map>
#include<string>
#include<memory>
#include"Item.h"

class ItemManager
{
private:
	std::map<std::string, std::unique_ptr<Item>> Itemdb;
	
	//�̱��� ���� ����
	ItemManager();
	~ItemManager();

public:
	static ItemManager& GetInstance();
	//�̱��� ���� ��ü�� �����ϴ� �Լ�

	ItemManager(const ItemManager&) = delete;
	//���� ���� ����

	ItemManager& operator=(const ItemManager&) = delete;
	//���� ����

	Item* CreateItem(const std::string& name);
	//db�� ���� ������ ����
};

