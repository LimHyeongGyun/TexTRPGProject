#include "ItemManager.h"
using namespace std;

ItemManager& ItemManager::GetInstance() {
    static ItemManager instance; // ��ü ��ü�� static����
    return instance;
}

ItemManager::ItemManager() {
    // === ���ӿ� �����ϴ� ��� �������� ������ ���⼭ �����ϰ� ��� ===

    Itemdb["������������"] = make_unique<Item>("���� ���� ����", ItemType::Potion,/*����*/50, 0, 0, 50);
    Itemdb["������������"] = make_unique<Item>("���� ���� ����", ItemType::Potion,/*����*/120, 0, 0, 100);
    Itemdb["������������"] = make_unique<Item>("���� ���� ����", ItemType::Potion,/*����*/250, 0, 0, 200);
    Itemdb["�����ռҵ�"] = make_unique<Item>("���� �ռҵ�", ItemType::Potion,/*����*/50, 25, 0, 0);
    Itemdb["��伮�ռҵ�"] = make_unique<Item>("��伮 �ռҵ�", ItemType::Potion,/*����*/100, 60, 0, 0);
    Itemdb["ö �ռҵ�"] = make_unique<Item>("��伮 �ռҵ�", ItemType::Potion,/*����*/250, 100, 0, 0);
    Itemdb["���װ���"] = make_unique<Item>("���� ����", ItemType::Potion,/*����*/50, 0, 0, 30);
    Itemdb["�罽����"] = make_unique<Item>("�罽 ����", ItemType::Potion,/*����*/250, 100, 0, 50);
    Itemdb["ö����"] = make_unique<Item>("ö ����", ItemType::Potion,/*����*/250, 100, 0, 100);
    Itemdb["����������"] = make_unique<Item>("������ ����", ItemType::Expendables,/*����*/20, 0, 0, 0);
    Itemdb["��ũ����������"] = make_unique<Item>("��ũ�� ���� ����", ItemType::Expendables,/*����*/100, 0, 0, 0);
    Itemdb["�巡�� ����"] = make_unique<Item>("�巡�� ����", ItemType::Expendables,/*����*/300, 0, 0, 0);
    Itemdb["����̻�"] = make_unique<Item>("��� �̻�", ItemType::Expendables,/*����*/30, 0, 0, 0);
}

ItemManager::~ItemManager() = default;

Item* ItemManager::CreateItem(const ::string& name) {
    auto it = Itemdb.find(name);
    if (it != Itemdb.end()) {
        // ������ ã������, Clone()�� ȣ���Ͽ� ����ǰ�� ����� ��ȯ
        return it->second->Clone();
    }
    return nullptr; // �ش��ϴ� �̸��� �������� ������ nullptr ��ȯ
}