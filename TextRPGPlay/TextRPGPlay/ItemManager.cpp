#include "ItemManager.h"

ItemManager& ItemManager::GetInstance() {
    static ItemManager instance; // ���α׷� ���� �� �ѹ��� ������
    return instance;
}

ItemManager::ItemManager() {
    // === ���ӿ� �����ϴ� ��� �������� ������ ���⼭ �����ϰ� ��� ===

    Itemdb["������������"] = std::make_unique<Item>("���� ���� ����", ItemType::Potion,/*����*/50, 0, 0, 50);
    Itemdb["������������"] = std::make_unique<Item>("���� ���� ����", ItemType::Potion,/*����*/120, 0, 0, 100);
    Itemdb["������������"] = std::make_unique<Item>("���� ���� ����", ItemType::Potion,/*����*/250, 0, 0, 200);
    Itemdb["�����ռҵ�"] = std::make_unique<Item>("���� �ռҵ�", ItemType::Potion,/*����*/50, 25, 0, 0);
    Itemdb["��伮�ռҵ�"] = std::make_unique<Item>("��伮 �ռҵ�", ItemType::Potion,/*����*/100, 60, 0, 0);
    Itemdb["ö �ռҵ�"] = std::make_unique<Item>("��伮 �ռҵ�", ItemType::Potion,/*����*/250, 100, 0, 0);
    Itemdb["���װ���"] = std::make_unique<Item>("���� ����", ItemType::Potion,/*����*/50, 0, 0, 30);
    Itemdb["�罽����"] = std::make_unique<Item>("�罽 ����", ItemType::Potion,/*����*/250, 100, 0, 50);
    Itemdb["ö����"] = std::make_unique<Item>("ö ����", ItemType::Potion,/*����*/250, 100, 0, 100);
    Itemdb["����������"] = std::make_unique<Item>("������ ����", ItemType::Potion,/*����*/20, 0, 0, 0);
    Itemdb["��ũ����������"] = std::make_unique<Item>("��ũ�� ���� ����", ItemType::Potion,/*����*/100, 0, 0, 0);
    Itemdb["�巡�� ����"] = std::make_unique<Item>("�巡�� ����", ItemType::Potion,/*����*/300, 0, 0, 0);
    Itemdb["����̻�"] = std::make_unique<Item>("��� �̻�", ItemType::Potion,/*����*/30, 0, 0, 0);



}

ItemManager::~ItemManager() = default;

Item* ItemManager::CreateItem(const std::string& name) {
    auto it = Itemdb.find(name);
    if (it != Itemdb.end()) {
        // ������ ã������, Clone()�� ȣ���Ͽ� ����ǰ�� ����� ��ȯ
        return it->second->Clone();
    }
    return nullptr; // �ش��ϴ� �̸��� �������� ������ nullptr ��ȯ
}