#pragma once
#include <vector>
#include <string>
#include "SingleTon.h"

// ĳ���� ����
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
	std::string name;					// ĳ���� �̸�
	int level;							// ����
	int hp;								// ü��
	int maxhp;							// �ִ�ü��
	int mp;								// ����
	int maxmp;							// �ִ븶��
	int attack;							// ���ݷ�
	int experience;						// ����ġ
	int experienceCapacity;				// ����ġ ��
	int gold;							// ���

	double damageReduction;				// ���ذ��� STR
	double accuracy;					// ���߷� DEX
	double skillEnhancement;			// ��ų��ȭ INT
	double criticalChance;				// ġ��ŸȮ�� LUK

	CharacterStat stat;					// ����
	int statStock;						// �ø����ִ� ���ݾ�
	int statStockAll;					// ��ü ���ݾ�

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

	// ĳ���� �ൿ
	int CharacterAttack();						// ����
	void ChracterUseItem();						// �����ۻ��

	void TakeDamage(int damage);				// ����������
};
