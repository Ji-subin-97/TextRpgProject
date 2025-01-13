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
	void CreateCharacter();								// 캐릭터생성
	void CreateRandomStat(Character& character);		// 캐릭터스텟
	void GenerateCharacter(Character& character);		// 스텟기반 캐릭터설정

	// 출력관련
	void PrintCharacterInfo();							// 캐릭터 정보출력
};