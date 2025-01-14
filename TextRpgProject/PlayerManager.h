#pragma once

#include <string>
#include "Singleton.h"
#include "Player.h"

using namespace std;

class PlayerManager : public SingleTon<PlayerManager>
{
private:
    friend class SingleTon<PlayerManager>;
    PlayerManager() = default;
    Player* player;
    bool IsValid(const string& name);
public:
    void DisplayInventory();
    void DisplayStat();
    void VisitShop();
    void CreatePlayer();
};

