#include <iostream>
#include <format>
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN 
#include <Windows.h>
#include "Character.h"
#include "Random.h"
#include "InputBox.h"
#include "LogBox.h"

using namespace std;

// 캐릭터 초기화
void Character::Init()
{
	level = 1;
	hp = 100;
	maxhp = 100;
	mp = 50;
	maxhp = 50;
	attack = 10;
	experience = 0;
	experienceCapacity = 50;
	gold = 0;

	damageReduction = 0;
	accuracy = 50.0;
	skillEnhancement = 0.0;
	criticalChance = 0.0;

	statStock = 0;
	statStockAll = 0;

	shared_ptr<CharacterManagerSystem> charManageSystem = make_shared<CharacterManagerSystem>();
	AddCharacterObserver(charManageSystem);
}

// 옵저버 등록
void Character::AddCharacterObserver(shared_ptr<CharacterObserver> observer)
{
	characterObservers.push_back(observer);
}

// 이벤트
void Character::NotifyLevelUpEvent()
{
	for (shared_ptr<CharacterObserver> item : characterObservers)
	{
		item->LevelUpEvent();
	}
}

// Getter
const std::string& Character::GetName() const
{
	return name;
}

int Character::GetLevel() const
{
	return level;
}

int Character::GetHp() const
{
	return hp;
}

int Character::GetMaxHp() const
{
	return maxhp;
}

int Character::GetMp() const
{
	return mp;
}

int Character::GetMaxMp() const
{
	return maxmp;
}

int Character::GetAttack() const
{
	return attack;
}

int Character::GetExperience() const
{
	return experience;
}

int Character::GetExperienceCapacity() const
{
	return experienceCapacity;
}

int Character::GetGold() const
{
	return gold;
}

int Character::GetDamageReduction() const
{
	return damageReduction;
}

double Character::GetAccuracy() const
{
	return accuracy;
}

double Character::GetSkillEnhancement() const
{
	return skillEnhancement;
}

double Character::GetCriticalChance() const
{
	return criticalChance;
}

CharacterStat Character::GetCharacterStat() const
{
	return stat;
}

int Character::GetStatStock() const
{
	return statStock;
}

int Character::GetStatStockAll() const
{
	return statStockAll;
}

// Setter
void Character::SetName(const string& _name)
{
	name = _name;
}

void Character::SetLevel(int _level)
{
	level = _level;
}

void Character::SetHp(int _hp)
{
	hp = _hp;
}

void Character::SetMaxHp(int _maxHp)
{
	maxhp = _maxHp;
}

void Character::SetMp(int _mp)
{
	mp = _mp;
}

void Character::SetMaxMp(int _maxMp)
{
	maxmp = _maxMp;
}

void Character::SetAttack(int _attack)
{
	attack = _attack;
}

void Character::SetExperience(int _experience)
{
	experience = _experience;
}

void Character::SetExperienceCapacity(int _expCapacity)
{
	experienceCapacity = _expCapacity;
}

void Character::SetGold(int _gold)
{
	gold = _gold;
}

void Character::SetDamageReduction(int _damageReduction)
{
	damageReduction = _damageReduction;
}

void Character::SetAccuracy(double _accuracy)
{
	accuracy = _accuracy;
}

void Character::SetSkillEnhancement(double _skillEnhancement)
{
	skillEnhancement = _skillEnhancement;
}

void Character::SetCriticalChance(double _criticalChance)
{
	criticalChance = _criticalChance;
}

void Character::SetCharacterStat(CharacterStat _stat)
{
	stat = _stat;
}

void Character::SetStatStock(int _statStock)
{
	statStock = _statStock;
}

void Character::SetStatStockAll(int _statStockAll)
{
	statStockAll = _statStockAll;
}

// 캐릭터 행동

void Character::CharacterLevelUp()
{
	// 레벨업 시 스텟5++, 레벨1++ 후 매니저에서 캐릭터능력치 조정
	level++;
	statStock += 5;

	NotifyLevelUpEvent();
}

int Character::CharacterAttack()
{
	// 공격계산 : 명중 실패시 데미지 0, 명중시 (공격력 * 1.3(치명타확률 배수는 1.3배))
	int attack = this->attack;
	double accuracy = this->accuracy;
	double randomScope = GetDoubleToRandom(0.0, 100.0);
	
	if (randomScope > accuracy)
	{
		LogBox::GetInstance()->Print(format("{} 님의 공격이 빗나갔습니다!", name));
		//cout << "[ " << name << " ] 님의 공격이 빗나갔습니다!" << endl;
		Sleep(1000);
		return 0;
	}

    double criticalChance = this->criticalChance;
	randomScope = GetDoubleToRandom(0.0, 100.0);

	if (randomScope < criticalChance)
	{
		attack = static_cast<int>(attack * 1.3);
		LogBox::GetInstance()->Print(format("{} 님의 공격이 {} 만큼 치명적인 데미지를 주었습니다!", name, attack));

		//cout << "[ " << name << " ] 님의 공격이 " << attack  << "만큼 치명적인 데미지를 주었습니다!" << endl;
	}
	else {
		LogBox::GetInstance()->Print(format("{} 님의 공격이 {} 만큼 데미지를 주었습니다!", name, attack));

		//cout << "[ " << name << " ] 님의 공격이 " << attack << "만큼 데미지를 주었습니다!" << endl;
	}
	Sleep(1000);

	return attack;
}

void Character::TakeDamage(int damage)
{
	// 데미지 계산: HP - (데미지 - 피해감소율) 단 0 미만 X
	damage = damage - damageReduction < 0 ? 0 : damage - damageReduction;
	LogBox::GetInstance()->Print(format("{} 님이 {} 만큼 데미지를 입었습니다!", name, damage));

	//cout << "[ " << name << " ] 님이 " << damage << "만큼 데미지를 입었습니다!" << endl;
	hp -= damage;
}

void Character::TakeExp(int exp)
{
	experience += exp;
	if (experience >= experienceCapacity)
	{
		CharacterLevelUp();
	}
}

void Character::TakeGold(int gold)
{
	this->gold += gold;
}

bool Character::IsDead()
{
	if (hp <= 0)
	{
		return true;
	}

	return false;
}

// 스킬관련 ===========================================================================================

void Character::PrintSkillList()
{
	//cout << "[ " << name << " ] 님이 현재 보유하고 있는 스킬목록 입니다." << endl;
	LogBox::GetInstance()->Print(format("{} 님이 현재 보유하고 있는 스킬목록 입니다.", name));

	int index = 1;
	for (const auto& item : skillInventory)
	{
		//cout << "[ " << index << " ] " << item->GetSkillName() << " / 데미지: " << item->GetDamage() << " / 소비마나: " << item->GetMp() << endl;
		LogBox::GetInstance()->Print
		(
			format("[{}] {} / 데미지: {} / 소비마나: {}",
			index, item->GetSkillName(), item->GetDamage(), item->GetMp()
		));
		index++;
	}
}

void Character::TakeSkill(unique_ptr<Skill> skill)
{
	//cout << "[ " << name << " ] 님이 " << skill->GetSkillName() << "스킬을 얻었습니다!" << endl;
	LogBox::GetInstance()->Print(format("{} 님이 {} 스킬을 얻었습니다!", name, skill->GetSkillName()));

	if (skillInventory.size() >= 3) {
		//cout << "더이상 스킬을 얻을 수 없습니다." << endl;
		LogBox::GetInstance()->Print(format("더이상 스킬을 얻을 수 없습니다."));

		Sleep(2000);
	}

	skillInventory.push_back(move(skill));

	Sleep(2000);
}

int Character::UseSkill()
{
	int choice = 0;
	int damage = 0;

	while (true)
	{
		// 사용할 스킬이 없을경우
		if (skillInventory.size() == 0)
		{
			//cout << "현재 사용할 수 있는 스킬이 없습니다." << endl;
			LogBox::GetInstance()->Print(format("현재 사용할 수 있는 스킬이 없습니다."));

			Sleep(1000);

			return -1;
		}

		PrintSkillList();
		LogBox::GetInstance()->Print(format("[ 0 ] 사용안함."));
		LogBox::GetInstance()->Print(format("사용하실 스킬을 선택해주세요."));
		choice = InputBox::GetInstance()->InputNumber();
		/*
		cout << "[ 0 ] 사용안함." << endl;
		cout << "사용하실 스킬을 선택해주세요." << endl;
		cout << "선택: ";
		cin >> choice;

		if (cin.fail())
		{
			cout << "숫자만 입력가능합니다." << endl;
			cin.clear();
			cin.ignore();

			continue;
		}
		*/

		// 사용안함 눌렀을시 -1 리턴
		if (choice == 0)
		{
			return -1;
		}

		const unique_ptr<Skill>& skill = skillInventory[choice - 1];

		if (skill != nullptr)
		{
			// 스킬소모마나가 MP보다 클시 사용불가
			if (mp < skill->GetMp())
			{
				LogBox::GetInstance()->Print(format("스킬에 필요한 마나가 부족합니다."));
				//cout << "스킬에 필요한 마나가 부족합니다." << endl;
				break;
			}

			damage = skill->GetDamage() + static_cast<int>(skill->GetDamage() * skillEnhancement / 100);
			//cout << "[ " << name << " ] 님의 " << skill->GetSkillName() << "!" << endl;
			LogBox::GetInstance()->Print(format("[{}] 님의 {} !", name, skill->GetSkillName()));
			mp -= skill->GetMp();

			break;
		}
		else
		{
			//cout << "스킬이 존재하지 않습니다." << endl;
			LogBox::GetInstance()->Print(format("스킬이 존재하지 않습니다."));

		}
	}

	return damage;
}
