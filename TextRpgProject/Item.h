#pragma once

#include "Entity.h"
#include "Pawn.h"

class Pawn;

class Item : public Entity
{
private:


public:
    void use(Pawn* pawn);
};

