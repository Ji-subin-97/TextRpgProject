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
	void GenerateCharacter(Character& character, bool isFirst);		// ���ݱ�� ĳ���ͼ���

	// ��°���
	void PrintCharacterInfoAll();						// ĳ���� ����������
	void PrintCharacterInfoStat(CharacterStat stat);	// ĳ���� �����������

	// ĳ���� �ɷ�ġ����
	void SetCharacterStat();							// ĳ������ ���ݰ���â

	// ����, ��ų, �̵�, ����, ȹ��� �ൿ�� ĳ���Ͱ� ����!
};