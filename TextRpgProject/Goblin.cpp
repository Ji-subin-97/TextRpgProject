#include "Goblin.h"
#include "Random.h"

using namespace std;

Goblin::Goblin(int playerLevel) {
	name = "°íºí¸°";

	int healthBase = GetIntToRandom(20, 30);
	int attackBase = GetIntToRandom(3, 5);
	health = playerLevel * healthBase;
	attack = playerLevel * attackBase;
}

void Goblin::TakeDamage(int attack)
{
	health -= attack;
}

int Goblin::DropExp()
{
	return GetIntToRandom(10, 15);
}

const string& Goblin::GetName() const
{
	return name;
}

int Goblin::GetHealth() const
{
	return health;
}

int Goblin::GetAttack() const
{
	return attack;
}

void Goblin::SetHealth(int health)
{
	this->health = health;
}

void Goblin::SetAttack(int attack)
{
	this->attack = attack;
}