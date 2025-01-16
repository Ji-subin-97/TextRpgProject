#pragma once
#include <vector>
#include <memory>
#include <iostream>
#include <string>
#include "Item.h"  
#include "SingleTon.h"

// 체력 포션 클래스
class HealPotion : public Item {
private:
    std::string name;
    int healthBoost;
    int buyPrice;
    int sellPrice;

public:
    HealPotion(std::string n, int h, int bp)
        : healthBoost(h) {
        name = n;
        buyPrice = bp;
        sellPrice = static_cast<int>(buyPrice * 0.6);
    }

    std::string GetName() const override { return name; }
    int GetHealthBoost() const override { return healthBoost; }
    int GetAttackBoost() const override { return 0; }
    int GetBuyPrice() const override { return buyPrice; }
    int GetSellPrice() const override { return sellPrice; }
};

// 공격력 상승 포션 클래스
class AttackBoostPotion : public Item {
private:
    std::string name;
    int attackBoost;
    int buyPrice;       
    int sellPrice;

public:
    AttackBoostPotion(std::string n, int a, int bp)
        : attackBoost(a) {
        name = n;
        buyPrice = bp;
        sellPrice = static_cast<int>(buyPrice * 0.6);
    }

    std::string GetName() const override { return name; }
    int GetHealthBoost() const override { return 0; }
    int GetAttackBoost() const override { return attackBoost; }
    int GetBuyPrice() const override { return buyPrice; }
    int GetSellPrice() const override { return sellPrice; }
};

// 아이템 매니저 클래스
class ItemManager : public SingleTon<ItemManager> {
private:
    std::vector<std::shared_ptr<Item>> allItems;
    friend class SingleTon<ItemManager>;

public:
    void initializeItems();
    std::vector<std::shared_ptr<Item>> getAllItems() const;
    std::shared_ptr<Item> getItemByIndex(int index);
    void displayAllItems() const;
    std::shared_ptr<Item> createItem(const std::string& itemType,
        const std::string& name,
        int value,
        int price);
};
