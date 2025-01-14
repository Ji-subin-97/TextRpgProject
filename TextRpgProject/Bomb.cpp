#include "Skill.h"

Bomb::Bomb()
{
	name = "ÆøÅº ´øÁö±â";
	skillType = SkillType::AD;
	damage = 50;
	mp = 20;
}

const std::string& Bomb::GetSkillName() const
{
	return name;
}

SkillType Bomb::GetSkillType() const
{
	return skillType;
}

int Bomb::GetDamage() const
{
	return damage;
}

int Bomb::GetMp() const
{
	return mp;
}