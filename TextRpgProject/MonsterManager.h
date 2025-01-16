#pragma once
#include "Monster.h"

class MonsterManager
{
public:
	Monster* CreateMonster(int num, int playerLevel);
	Monster* CreateBossMonster();
};