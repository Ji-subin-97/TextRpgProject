#pragma once

#include "Pawn.h"
#include "struct.h"

class Human : public Pawn
{
private:
    int id = (int)PawnId::HUMAN;
    string name = "�ΰ�";
    BaseAbility baseAbility = { 200, 30 };

public:
    Human(int _level);
};
