#pragma once
#pragma once
#include "Monster.h"

class Human : public Monster
{
private:
	std::string name;
	int health;
	int attack;
public:
	Human(int playerLevel);
	~Human() {}

	int MonsterAttack() override;
	void TakeDamage(int attack) override;
	int DropExp() override;
	int DropGold() override;
	void Die() override;

	bool IsBoss() override;

	const std::string& GetName() const override;
	int GetHealth() const override;
	int GetAttack() const override;
	void SetHealth(int health) override;
	void SetAttack(int attack) override;
};