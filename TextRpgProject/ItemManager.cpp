#include "ItemManager.h"

void ItemManager::initializeItems() {
    if (allItems.empty()) {
        allItems.push_back(std::make_shared<HealPotion>("체력 포션", 50, 10));
        allItems.push_back(std::make_shared<AttackBoostPotion>("공격력 버프 포션", 10, 15));
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
    std::cout << "\n===== 아이템 목록 =====\n";
    int index = 1;
    for (const auto& item : allItems) {
        std::cout << index++ << ". " << item->GetName()
            << " (체력 +" << item->GetHealthBoost()
            << ", 공격력 +" << item->GetAttackBoost()
            << ") - 구매가: " << item->GetBuyPrice()
            << " 골드, 판매가: " << item->GetSellPrice() << " 골드\n";
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