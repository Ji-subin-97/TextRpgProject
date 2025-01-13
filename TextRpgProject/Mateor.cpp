#include "Skill.h"

Meteor::Meteor()
{
	name = "���׿�";
	skillType = SkillType::AD;
	damage = 70;
	mp = 30;
}

const std::string& Meteor::GetSkillName() const
{
	return name;
}

SkillType Meteor::GetSkillType() const
{
	return skillType;
}

int Meteor::GetDamage() const
{
	return damage;
}

int Meteor::GetMp() const
{
	return mp;
}