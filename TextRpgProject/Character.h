#pragma once
#include <vector>
#include <string>
#include "SingleTon.h"

// 캐릭터 스텟
struct CharacterStat
{
	int HP = 0;
	int MP = 0;
	int STR = 0;
	int DEX = 0;
	int INT = 0;
	int LUK = 0;
};

class Character : public SingleTon<Character>
{
private:
	std::string name;					// 캐릭터 이름
	int level;							// 레벨
	int hp;								// 체력
	int maxhp;							// 최대체력
	int mp;								// 마나
	int maxmp;							// 최대마나
	int attack;							// 공격력
	int experience;						// 경험치
	int experienceCapacity;				// 경험치 통
	int gold;							// 골드

	double damageReduction;				// 피해감소 STR
	double accuracy;					// 명중률 DEX
	double skillEnhancement;			// 스킬강화 INT
	double criticalChance;				// 치명타확률 LUK

	CharacterStat stat;					// 스텟
	int statStock;						// 올릴수있는 스텟양
	int statStockAll;					// 전체 스텟양

	Character() = default;
	~Character() = default;

	friend class SingleTon<Character>;
public:
	void Init();

	const std::string& GetName() const;
	int GetLevel() const;
	int GetHp() const;
	int GetMaxHp() const;
	int GetMp() const;
	int GetMaxMp() const;
	int GetAttack() const;
	int GetExperience() const;
	int GetExperienceCapacity() const;
	int GetGold() const;
	double GetDamageReduction() const;
	double GetAccuracy() const;
	double GetSkillEnhancement() const;
	double GetCriticalChance() const;
	CharacterStat GetCharacterStat() const;
	int GetStatStock() const;
	int GetStatStockAll() const;

	void SetName(const std::string& _name);
	void SetLevel(int _level);
	void SetHp(int _hp);
	void SetMaxHp(int _maxHp);
	void SetMp(int _mp);
	void SetMaxMp(int _maxMp);
	void SetAttack(int _attack);
	void SetExperience(int _experience);
	void SetExperienceCapacity(int _expCapacity);
	void SetGold(int _gold);
	void SetDamageReduction(double _damageReduction);
	void SetAccuracy(double _accuracy);
	void SetSkillEnhancement(double _skillEnhancement);
	void SetCriticalChance(double _criticalChance);
	void SetCharacterStat(CharacterStat _stat);
	void SetStatStock(int _statStock);
	void SetStatStockAll(int _statStockAll);

	// 캐릭터 행동
	int CharacterAttack();						// 공격
	void ChracterUseItem();						// 아이템사용

	void TakeDamage(int damage);				// 데미지입음
};
