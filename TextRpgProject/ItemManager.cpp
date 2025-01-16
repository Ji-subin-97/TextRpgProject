#include "ItemManager.h"

void ItemManager::initializeItems() {
    if (allItems.empty()) {
        allItems.push_back(std::make_shared<HealPotion>("ü�� ����", 50, 10));
        allItems.push_back(std::make_shared<AttackBoostPotion>("���ݷ� ���� ����", 10, 15));
    }
}
std::vector<std::shared_ptr<Item>> ItemManager::getAllItems() const {
    return allItems;
}

std::shared_ptr<Item> ItemManager::getItemByIndex(int index) {
    if (index < 1 || index > allItems.size()) {
        return nullptr;
    }
    return allItems[index - 1];
}

void ItemManager::displayAllItems() const {
    std::cout << "\n===== ������ ��� =====\n";
    int index = 1;
    for (const auto& item : allItems) {
        std::cout << index++ << ". " << item->GetName()
            << " (ü�� +" << item->GetHealthBoost()
            << ", ���ݷ� +" << item->GetAttackBoost()
            << ") - ���Ű�: " << item->GetBuyPrice()
            << " ���, �ǸŰ�: " << item->GetSellPrice() << " ���\n";
    }
}

std::shared_ptr<Item> ItemManager::createItem(const std::string& itemType,
    const std::string& name,
    int value,
    int price) {
    if (itemType == "HealPotion") {
        return std::make_shared<HealPotion>(name, value, price);
    }
    else if (itemType == "AttackBoostPotion") {
        return std::make_shared<AttackBoostPotion>(name, value, price);
    }
    return nullptr;
}