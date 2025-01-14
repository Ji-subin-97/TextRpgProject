#pragma once

#include "Singleton.h"
#include "Player.h"

// ���� ���� Ŭ����
class TradeManager : public Singleton<TradeManager>
{
private:
    friend class Singleton<TradeManager>;
    TradeManager() = default;
public:
    void DisplayItems();
    void BuyItem(Player* player, int itemId, int count);
    void SellItem(Player* player, int itemId, int count);
};