#include "Skill.h"

Sparata::Sparata()
{
	name = "���ĸ�Ÿ!!!";
	skillType = SkillType::AD;
	damage = 999;
	mp = 1;
}

const std::string& Sparata::GetSkillName() const
{
	return name;
}

SkillType Sparata::GetSkillType() const
{
	return skillType;
}

int Sparata::GetDamage() const
{
	return damage;
}

int Sparata::GetMp() const
{
	return mp;
}