#pragma once
#include <vector>
#include <string>
#include "Item.h"

class Character {
private:
	static Character* instance;
	std::string name;
	int level;
	int health;
	int maxHealth;
	int attack;
	int experience;
	int gold;
	std::vector<Item*> inventory;

	Character() 
		: level(1), health(200), maxHealth(200), attack(30), experience(0), gold(0) {}
	~Character() {}
public:
	Character(const Character& character) = delete;
	Character& operator=(const Character&) = delete;

	static Character* getInstance() 
	{
		if (instance == nullptr)
		{
			instance = new Character();
		}
		return instance;
	}

};