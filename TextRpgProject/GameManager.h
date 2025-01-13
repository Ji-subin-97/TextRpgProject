#pragma once

#include <string>
#include "PlayerManager.h"
#include "FactoryManager.h"
#include "BattleManager.h"
#include "TradeManager.h"
#include "Singleton.h"

using namespace std;

class GameManager : public Singleton<GameManager>
{
    friend class Singleton<GameManager>;
     
private:
    GameManager() = default;

    string gameName = "TextRPG";
    PlayerManager* playerManager;
    FactoryManager* factoryManager;
    BattleManager* battleManager;
    TradeManager* tradeManager;

    void InitManager();
public:
    void StartGame();
    void ProgressGame();
    void SelectOption();
    void EncounterEnemy();
};

