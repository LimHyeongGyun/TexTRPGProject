#include "ItemManager.h"

ItemManager& ItemManager::GetInstance() {
    static ItemManager instance; // ���α׷� ���� �� �ѹ��� ������
    return instance;
}

ItemManager::ItemManager() {
    // === ���ӿ� �����ϴ� ��� �������� ������ ���⼭ �����ϰ� ��� ===
    prototypes["��������"] = std::make_unique<Potion>("���� ����", 50, 20);
    prototypes["�ռҵ�"] = std::make_unique<Weapon>("�ռҵ�", 150, 10);
    prototypes["���װ���"] = std::make_unique<Armor>("���� ����", 100, 20);
    prototypes["ö����"] = std::make_unique<Armor>("ö����", 200, 50);

}

ItemManager::~ItemManager() = default;

Item* ItemManager::CreateItem(const std::string& name) {
    auto it = prototypes.find(name);
    if (it != prototypes.end()) {
        // ������ ã������, Clone()�� ȣ���Ͽ� ����ǰ�� ����� ��ȯ
        return it->second->Clone();
    }
    return nullptr; // �ش��ϴ� �̸��� �������� ������ nullptr ��ȯ
}