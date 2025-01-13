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
	void CreateCharacter();								// ĳ���ͻ���
	void CreateRandomStat(Character& character);		// ĳ���ͽ���
	void GenerateCharacter(Character& character);		// ���ݱ�� ĳ���ͼ���

	// ��°���
	void PrintCharacterInfo();							// ĳ���� �������
};