#pragma once
#include "SingleTon.h"
#include "Character.h"
#include "SkillManager.h"

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
	void SetCharacterStatAfterLevelUp();				// ĳ���� ������ �� ���ݰ���(������ �̺�Ʈ �߻� ��)
	void SetCharacterExp(int caseNum);					// ĳ���� ������ġ ����

	// ĳ���� ��ų����
	void CharacterGetSkill();							// ĳ���� ��ųȹ��

	// ����, ��ų, �̵�, ����, ȹ��� �ൿ�� ĳ���Ͱ� ����!
};