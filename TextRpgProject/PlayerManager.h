#pragma once

#include <string>
#include "Singleton.h"
#include "Player.h"

using namespace std;

class PlayerManager : public Singleton<PlayerManager>
{
private:
    friend class Singleton<PlayerManager>;
    PlayerManager() = default;
    Player* player;
    bool IsValid(const string& name);
public:
    void DisplayInventory();
    void DisplayStat();
    void VisitShop();
    void CreatePlayer();
};

