#pragma once
#include "SingleTon.h"
#include "Character.h"
#include "SkillManager.h"
#include <unordered_map>
#include <string>

using namespace std;

class CharacterManager : public SingleTon<CharacterManager>
{
private:
	CharacterManager() = default;
	~CharacterManager() = default;

	friend class SingleTon<CharacterManager>;
public:
	void CreateCharacter();								// 캐릭터생성
	Character* GetCharacter();	// 현재 캐릭터 가져오기
	void CreateRandomStat(Character& character);		// 캐릭터스텟
	void GenerateCharacter(Character& character, bool isFirst);		// 스텟기반 캐릭터설정

	// 출력관련
	void PrintCharacterInfoAll();						// 캐릭터 모든정보출력
	void PrintCharacterInfoStat(CharacterStat stat);	// 캐릭터 스텟정보출력

	// 캐릭터 능력치관련
	void SetCharacterStat();							// 캐릭터의 스텟관리창
	void SetCharacterStatAfterLevelUp();				// 캐릭터 레벨업 후 스텟관리(레벨업 이벤트 발생 시)
	void SetCharacterExp(int caseNum);					// 캐릭터 레벨수치 관리

	// 캐릭터 능력지 반환
	unordered_map<string, string> GetCharacterStat() const;

	// 캐릭터 스킬관련
	void CharacterGetSkill();							// 캐릭터 스킬획득

	// 공격, 스킬, 이동, 장착, 획득등 행동은 캐릭터가 직접!
};