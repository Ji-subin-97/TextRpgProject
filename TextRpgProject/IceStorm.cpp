#include "Skill.h"

IceStorm::IceStorm()
{
	name = "���̽�����";
	skillType = SkillType::AP;
	damage = 20;
	mp = 10;
}

const std::string& IceStorm::GetSkillName() const
{
	return name;
}

SkillType IceStorm::GetSkillType() const
{
	return skillType;
}

int IceStorm::GetDamage() const
{
	return damage;
}

int IceStorm::GetMp() const
{
	return mp;
}