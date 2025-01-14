#include "MonsterManager.h"
#include "MonsterType.h"
#include "Slime.h"
#include "Goblin.h"
#include "GoldenGoblin.h"
#include "Orc.h"
#include "Troll.h"
#include "Human.h"
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
	case 3:
		monster = new Orc(playerLevel);
		break;
	case 4:
		monster = new Troll(playerLevel);
		break;
	case 5:
		monster = new Human(playerLevel);
		break;
	default:
		monster = new Slime(playerLevel);
		break;
	}

	return monster;
}

Monster* MonsterManager::CreateBossMonster()
{
	Monster* monster = new GoldenGoblin(0);

	return monster;
}