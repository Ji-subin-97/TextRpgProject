#pragma once

class CharacterObserver
{
public:
	virtual ~CharacterObserver() = default;
	virtual void LevelUpEvent() = 0;
};

class CharacterManagerSystem : public CharacterObserver
{
public:
	void LevelUpEvent() override;
};