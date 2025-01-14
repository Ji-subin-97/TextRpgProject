#include "Skill.h"

FireBall::FireBall()
{
	name = "파이어볼";
	skillType = SkillType::AP;
	damage = 10;
	mp = 7;
}

const std::string& FireBall::GetSkillName() const
{
	return name;
}

SkillType FireBall::GetSkillType() const
{
	return skillType;
}

int FireBall::GetDamage() const
{
	return damage;
}

int FireBall::GetMp() const
{
	return mp;
}