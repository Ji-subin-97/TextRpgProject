#include "Character.h"

using namespace std;

// 캐릭터 초기화
void Character::Init()
{
	level = 1;
	hp = 100;
	maxhp = 100;
	mp = 50;
	maxhp = 50;
	attack = 10;
	experience = 0;
	experienceCapacity = 50;
	gold = 0;

	damageReduction = 0.0;
	accuracy = 50.0;
	skillEnhancement = 0.0;
	criticalChance = 0.0;

	statStock = 0;
	statStockAll = 0;
}

// Getter
const std::string& Character::GetName() const
{
	return name;
}

int Character::GetLevel() const
{
	return level;
}

int Character::GetHp() const
{
	return hp;
}

int Character::GetMaxHp() const
{
	return maxhp;
}

int Character::GetMp() const
{
	return mp;
}

int Character::GetMaxMp() const
{
	return maxmp;
}

int Character::GetAttack() const
{
	return attack;
}

int Character::GetExperience() const
{
	return experience;
}

int Character::GetExperienceCapacity() const
{
	return experienceCapacity;
}

int Character::GetGold() const
{
	return gold;
}

double Character::GetDamageReduction() const
{
	return damageReduction;
}

double Character::GetAccuracy() const
{
	return accuracy;
}

double Character::GetSkillEnhancement() const
{
	return skillEnhancement;
}

double Character::GetCriticalChance() const
{
	return criticalChance;
}

CharacterStat Character::GetCharacterStat() const
{
	return stat;
}

int Character::GetStatStock() const
{
	return statStock;
}

int Character::GetStatStockAll() const
{
	return statStockAll;
}

// Setter
void Character::SetName(const string& _name)
{
	name = _name;
}

void Character::SetLevel(int _level)
{
	level = _level;
}

void Character::SetHp(int _hp)
{
	hp = _hp;
}

void Character::SetMaxHp(int _maxHp)
{
	maxhp = _maxHp;
}

void Character::SetMp(int _mp)
{
	mp = _mp;
}

void Character::SetMaxMp(int _maxMp)
{
	maxmp = _maxMp;
}

void Character::SetAttack(int _attack)
{
	attack = _attack;
}

void Character::SetExperience(int _experience)
{
	experience = _experience;
}

void Character::SetExperienceCapacity(int _expCapacity)
{
	experienceCapacity = _expCapacity;
}

void Character::SetGold(int _gold)
{
	gold = _gold;
}

void Character::SetDamageReduction(double _damageReduction)
{
	damageReduction = _damageReduction;
}

void Character::SetAccuracy(double _accuracy)
{
	accuracy = _accuracy;
}

void Character::SetSkillEnhancement(double _skillEnhancement)
{
	skillEnhancement = _skillEnhancement;
}

void Character::SetCriticalChance(double _criticalChance)
{
	criticalChance = _criticalChance;
}

void Character::SetCharacterStat(CharacterStat _stat)
{
	stat = _stat;
}

void Character::SetStatStock(int _statStock)
{
	statStock = _statStock;
}

void Character::SetStatStockAll(int _statStockAll)
{
	statStockAll = _statStockAll;
}


