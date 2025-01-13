#pragma once

#include "Singleton.h"

// 전투 관리 클래스
class BattleManager : public Singleton<BattleManager>
{
    friend class Singleton<BattleManager>;
    BattleManager() = default;
public:
    void Battle();
};
