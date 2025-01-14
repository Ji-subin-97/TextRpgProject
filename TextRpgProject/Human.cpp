#include <iostream>
#include "Human.h"
#include "Random.h"

using namespace std;

Human::Human(int playerLevel) {
	name = "인간";

	int healthBase = GetIntToRandom(60, 70);
	int attackBase = GetIntToRandom(20, 30);
	health = playerLevel * healthBase;
	attack = playerLevel * attackBase;
}

int Human::MonsterAttack()
{
	cout << "검을 휘두르기 시작했다." << endl;

	return attack;
}

void Human::TakeDamage(int attack)
{
	health -= attack;
}

int Human::DropExp()
{
	return GetIntToRandom(50, 80);
}

int Human::DropGold()
{
	return GetIntToRandom(100, 150);
}

void Human::Die()
{
	cout << "그는 죽었다." << endl;
}

const string& Human::GetName() const
{
	return name;
}

int Human::GetHealth() const
{
	return health;
}

int Human::GetAttack() const
{
	return attack;
}

void Human::SetHealth(int health)
{
	this->health = health;
}

void Human::SetAttack(int attack)
{
	this->attack = attack;
}