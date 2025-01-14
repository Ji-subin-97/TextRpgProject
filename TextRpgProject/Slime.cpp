#include <iostream>
#include "Slime.h"
#include "Random.h"

using namespace std;

Slime::Slime(int playerLevel) {
	name = "슬라임";
	isBoss = false;

	int healthBase = GetIntToRandom(5, 10);
	int attackBase = GetIntToRandom(1, 3);
	health = playerLevel * healthBase;
	attack = playerLevel * attackBase;
}
 
int Slime::MonsterAttack()
{
	cout << "슬라임은 출렁거리며 돌진했다." << endl;

	return attack;
}

void Slime::TakeDamage(int attack)
{
	health -= attack;
}

int Slime::DropExp()
{
	return GetIntToRandom(30, 35);
}

int Slime::DropGold()
{
	return GetIntToRandom(10, 20);
}

void Slime::Die()
{
	cout << "슬라임은 녹아버렸다." << endl;
}

bool Slime::IsBoss()
{
	return isBoss;
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