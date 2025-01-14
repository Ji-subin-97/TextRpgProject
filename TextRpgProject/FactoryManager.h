#pragma once

#include "Singleton.h"
#include "Pawn.h"
#include "struct.h"

// �� ���� ���� Ŭ����
class FactoryManager : public Singleton<FactoryManager>
{
private:
    friend class Singleton<FactoryManager>;
    FactoryManager() = default;
public:
    Pawn* GeneratePawn(PawnId id, int level);
    //ü�¡����ݷ��� ���� ������ 1.5�� ������ �������� ����
    Pawn* GenerateBoss(bool isBoss);
};

