#pragma once

#include <vector>
#include "Entity.h"
#include "Item.h"

using namespace std;

class Item;

class Pawn : public Entity
{
private:
    int level;
    int health;
    int attack;
    int gold;
    int experience;
    vector<Item*> inventory;

public:
    void SetLevel(int _level);
    int GetLevel() const;
    void SetHealth(int _health);
    int GetHealth() const;
    void SetAttack(int _attack);
    int GetAttack() const;
    Item* DropItem();
};

