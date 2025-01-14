#include "Random.h"
#include "SkillManager.h"

using namespace std;

unique_ptr<Skill> SkillManager::TakeSkillRandom()
{
	int randomNum = GetIntToRandom(1, 5);
	unique_ptr<Skill> skill;

	switch (randomNum)
	{
	case 1:
		skill = make_unique<FireBall>();
		break;
	case 2:
		skill = make_unique<IceStorm>();
		break;
	case 3:
		skill = make_unique<Bomb>();
		break;
	case 4:
		skill = make_unique<Meteor>();
		break;
	case 5:
		skill = make_unique<Sparata>();
		break;
	default:
		skill = make_unique<FireBall>();
		break;
	}

	return move(skill);
}