#pragma once
#include <string>

class Item {
public:
    virtual ~Item() = default;
    virtual std::string GetName() const = 0;
    virtual int GetHealthBoost() const = 0;
    virtual int GetAttackBoost() const = 0;
    virtual int GetBuyPrice() const = 0;
    virtual int GetSellPrice() const = 0;
};