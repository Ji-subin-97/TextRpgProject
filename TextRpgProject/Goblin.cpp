#include <iostream>
#include "Goblin.h"
#include "Random.h"
#include "LogBox.h"

using namespace std;

Goblin::Goblin(int playerLevel) {
	name = "고블린";
	isBoss = false;

	int healthBase = GetIntToRandom(10, 20);
	int attackBase = GetIntToRandom(2, 4);
	health = playerLevel * healthBase;
	attack = playerLevel * attackBase;
}

int Goblin::MonsterAttack()
{
	LogBox::GetInstance()->Print("고블린은 공격해왔다.");
	//cout << "고블린은 공격해왔다." << endl;

	return attack;
}

void Goblin::TakeDamage(int attack)
{
	health -= attack;
}

int Goblin::DropExp()
{
	return GetIntToRandom(40, 45);
}

int Goblin::DropGold()
{
	return GetIntToRandom(30, 50);
}

void Goblin::Die()
{
	LogBox::GetInstance()->Print("고블린은 더이상 심장이 뛰지 않는다.");
	//cout << "고블린은 더이상 심장이 뛰지 않는다." << endl;
}

bool Goblin::IsBoss()
{
	return isBoss;
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