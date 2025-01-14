#pragma once

#include "SingleTon.h"
#include "Pawn.h"
#include "struct.h"

// 몹 생성 관리 클래스
class FactoryManager : public SingleTon<FactoryManager>
{
private:
    friend class SingleTon<FactoryManager>;
    FactoryManager() = default;
public:
    Pawn* GeneratePawn(PawnId id, int level);
    //체력·공격력은 기존 몬스터의 1.5배 범위를 랜덤으로 설정
    Pawn* GenerateBoss(bool isBoss);
};

