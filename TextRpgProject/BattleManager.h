#pragma once

#include "Singleton.h"

// ���� ���� Ŭ����
class BattleManager : public Singleton<BattleManager>
{
    friend class Singleton<BattleManager>;
    BattleManager() = default;
public:
    void Battle();
};
