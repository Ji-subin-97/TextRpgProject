#pragma once

#include "SingleTon.h"
#include "Pawn.h"
#include "struct.h"

// �� ���� ���� Ŭ����
class FactoryManager : public SingleTon<FactoryManager>
{
private:
    friend class SingleTon<FactoryManager>;
    FactoryManager() = default;
public:
    Pawn* GeneratePawn(PawnId id, int level);
    //ü�¡����ݷ��� ���� ������ 1.5�� ������ �������� ����
    Pawn* GenerateBoss(bool isBoss);
};

