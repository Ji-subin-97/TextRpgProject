#pragma once
#include <vector>
#include <string>
#include <memory>
#include <map>
#include "SingleTon.h"
#include "CharacterObserver.h"
#include "SkillManager.h"


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
	// ������
	std::vector<std::shared_ptr<CharacterObserver>> characterObservers;

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

	int damageReduction;				// ���ذ��� STR
	double accuracy;					// ���߷� DEX
	double skillEnhancement;			// ��ų��ȭ INT
	double criticalChance;				// ġ��ŸȮ�� LUK

	CharacterStat stat;					// ����
	int statStock;						// �ø����ִ� ���ݾ�
	int statStockAll;					// ��ü ���ݾ�

	std::vector<std::unique_ptr<Skill>> skillInventory;		// ��ų �κ��丮

	Character() = default;
	~Character() = default;

	friend class SingleTon<Character>;
public:
	void Init();

	// ������ ���
	void AddCharacterObserver(std::shared_ptr<CharacterObserver> observer);
	// �̺�Ʈ
	void NotifyLevelUpEvent();

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
	int GetDamageReduction() const;
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
	void SetDamageReduction(int _damageReduction);
	void SetAccuracy(double _accuracy);
	void SetSkillEnhancement(double _skillEnhancement);
	void SetCriticalChance(double _criticalChance);
	void SetCharacterStat(CharacterStat _stat);
	void SetStatStock(int _statStock);
	void SetStatStockAll(int _statStockAll);

	// ĳ���� �ൿ
	void CharacterLevelUp();					// ������
	int CharacterAttack();						// ����
	
	void TakeDamage(int damage);				// ����������
	void TakeExp(int exp);						// ����ġ����

	// �����۰���
	// void PrintItemList();					// ĳ���Ͱ� ���簡�����ִ� ������ ���
	// void TakeItem(Item item);				// ������ ���
	// void UseItem();							// ������ ���

	// ��ų����
	void PrintSkillList();						// ĳ���Ͱ� ���簡�����ִ� ��ų ���
	void TakeSkill(std::unique_ptr<Skill> skill);		// ��ų���
	int UseSkill();								// ��ų���
};
