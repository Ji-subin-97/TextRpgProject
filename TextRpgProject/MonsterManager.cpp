#include "MonsterManager.h"
#include "MonsterType.h"
#include "Slime.h"
#include "Goblin.h"
#include "Random.h"

Monster* MonsterManager::CreateMonster(int num, int playerLevel)
{
	Monster* monster = nullptr;
	int monsterNum = GetIntToRandom(1, num);

	switch (monsterNum)
	{
	case 1:
		monster = new Slime(playerLevel);
		break;
	case 2:
		monster = new Goblin(playerLevel);
		break;
	default:
		monster = new Slime(playerLevel);
		break;
	}

	return monster;
}