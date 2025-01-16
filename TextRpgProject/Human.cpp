#include <iostream>
#include "Human.h"
#include "Random.h"
#include "LogBox.h"

using namespace std;

Human::Human(int playerLevel) {
	name = "인간";
	isBoss = false;

	int healthBase = GetIntToRandom(40, 50);
	int attackBase = GetIntToRandom(9, 11);
	health = playerLevel * healthBase;
	attack = playerLevel * attackBase;
}

int Human::MonsterAttack()
{
	LogBox::GetInstance()->Print("검을 휘두르기 시작했다.");
	//cout << "검을 휘두르기 시작했다." << endl;

	return attack;
}

void Human::TakeDamage(int attack)
{
	health -= attack;
}

int Human::DropExp()
{
	return GetIntToRandom(100, 150);
}

int Human::DropGold()
{
	return GetIntToRandom(100, 150);
}

void Human::Die()
{
	LogBox::GetInstance()->Print("그는 죽었다.");
	//cout << "그는 죽었다." << endl;
}

bool Human::IsBoss()
{
	return isBoss;
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