#pragma once
#include <string>

class Monster
{
protected:
	bool isBoss;
public:
	Monster() {}
	Monster(int playerLevel) {};
	virtual ~Monster() {}

	virtual int MonsterAttack() = 0;
	virtual void TakeDamage(int attack) = 0;
	virtual int DropExp() = 0;
	virtual int DropGold() = 0;
	virtual void Die() = 0;

	virtual bool IsBoss() = 0;

	virtual const std::string& GetName() const = 0;
	virtual int GetHealth() const = 0;
	virtual int GetAttack() const = 0;
	virtual void SetHealth(int health) = 0;
	virtual void SetAttack(int attack) = 0;
};