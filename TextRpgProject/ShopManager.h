#pragma once
#include <map>
#include <memory>
#include <iostream>
#include "ItemManager.h"
#include "Character.h"
#include "Item.h"
#include "SingleTon.h"

class ShopManager : public SingleTon<ShopManager> {
private:
    std::map<std::shared_ptr<Item>, int> inventory;
    friend class SingleTon<ShopManager>;
    void manageInventory(Character& player) const;
    
public:
    void initializeInventory();
    void DisplayItems() const;
    bool buyItem(int index, Character& player);
    bool sellItem(int index, Character& player);
    size_t itemCount() const;
    void VisitShop(Character& player);
};
