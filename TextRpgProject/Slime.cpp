#include "Slime.h"
#include "Random.h"

using namespace std;

Slime::Slime(int playerLevel) {
	name = "½½¶óÀÓ";

	int healthBase = GetIntToRandom(5, 10);
	int attackBase = GetIntToRandom(1, 3);
	health = playerLevel * healthBase;
	attack = playerLevel * attackBase;
}

void Slime::TakeDamage(int attack)
{
	health -= attack;
}

int Slime::DropExp()
{
	return GetIntToRandom(5, 7);
}

const string& Slime::GetName() const
{
	return name;
}

int Slime::GetHealth() const
{
	return health;
}

int Slime::GetAttack() const
{
	return attack;
}

void Slime::SetHealth(int health)
{
	this->health = health;
}

void Slime::SetAttack(int attack)
{
	this->attack = attack;
}