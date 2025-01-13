#pragma once
#include "SingleTon.h"
#include "Character.h"

class CharacterManager : public SingleTon<CharacterManager>
{
private:
	CharacterManager() = default;
	~CharacterManager() = default;

	friend class SingleTon<CharacterManager>;
public:
	void CreateCharacter();
	void CreateRandomStat(Character& character);
};