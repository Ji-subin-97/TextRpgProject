#pragma once
#include "Monster.h"

class Slime : public Monster
{
private:
	std::string name;
	int health;
	int attack;
public:
	Slime(int playerLevel);
	~Slime() {}

	void TakeDamage(int attack);
	int DropExp();

	const std::string& GetName() const;
	int GetHealth() const;
	int GetAttack() const;
	void SetHealth(int health);
	void SetAttack(int attack);
};