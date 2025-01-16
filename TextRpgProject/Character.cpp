#include <iostream>
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN 
#include <Windows.h>
#include "Character.h"
#include "Random.h"

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
	attackBonus = 0;
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

int Character::GetAttackBonus() const
{
	return attackBonus;
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

void Character::SetAttackBonus(int _attackBonus)
{
	attackBonus = _attackBonus;
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
	int attack = this->attack + attackBonus;	// 아이템 기능 추가로인한 보너스공격력 추가.
	double accuracy = this->accuracy;
	double randomScope = GetDoubleToRandom(0.0, 100.0);

	if (randomScope > accuracy)
	{
		cout << "[ " << name << " ] 님의 공격이 빗나갔습니다!" << endl;
		Sleep(1000);
		return 0;
	}

	double criticalChance = this->criticalChance;
	randomScope = GetDoubleToRandom(0.0, 100.0);

	if (randomScope < criticalChance)
	{
		attack = static_cast<int>(attack * 1.3);
		cout << "[ " << name << " ] 님의 공격이 " << attack << "만큼 치명적인 데미지를 주었습니다!" << endl;
	}
	else {
		cout << "[ " << name << " ] 님의 공격이 " << attack << "만큼 데미지를 주었습니다!" << endl;
	}
	Sleep(1000);

	return attack;
}

void Character::TakeDamage(int damage)
{
	// 데미지 계산: HP - (데미지 - 피해감소율) 단 0 미만 X
	damage = damage - damageReduction < 0 ? 0 : damage - damageReduction;
	cout << "[ " << name << " ] 님이 " << damage << "만큼 데미지를 입었습니다!" << endl;
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

// 아이템관련
void Character::PrintItemList()
{
	std::cout << "\n===== " << name << "의 인벤토리 =====\n";
	int index = 1;
	for (const auto& pair : inventory) {
		const auto& item = pair.first;
		int quantity = pair.second;
		std::cout << "[ " << index++ << " ] " << item->GetName()
			<< " (체력 +" << item->GetHealthBoost()
			<< ", 공격력 +" << item->GetAttackBoost()
			<< ") x" << quantity << "개\n";
	}
}

int Character::UseItem()
{
	int choice = 0;

	while (true)
	{
		if (inventory.empty())
		{
			cout << "현재 보유하고 있는 아이템이 없습니다." << endl;
			Sleep(1500);
			break;
		}

		PrintItemList();
		cout << "[ 0 ] 사용안함." << endl;
		cout << "사용하실 아이템을 선택해주세요." << endl;
		cout << "선택: ";
		cin >> choice;

		if (cin.fail())
		{
			cout << "숫자만 입력가능합니다." << endl;
			cin.clear();
			cin.ignore();

			continue;
		}

		// 사용안함 눌렀을시 -1 리턴
		if (choice == 0)
		{
			return -1;
		}

		int attackBoost = 0;
		int healthBoost = 0;

		auto item = GetItem(choice);
		if (!item) {
			std::cout << "잘못된 아이템 번호입니다.\n";
			continue;
		}
		else
		{
			attackBoost = item->GetAttackBoost();
			healthBoost = item->GetHealthBoost();

			cout << "[ " << name << " ] 은 " << item->GetName() << "아이템을 사용하였습니다!" << endl;
			if (attackBoost > 0) AttackBoost(attackBoost);
			if (healthBoost > 0) Heal(healthBoost);

			RemoveItem(item);

			break;
		}
	}

	return 1;
}

void Character::Heal(int health)
{
	cout << "캐릭터가 " << health << "만큼 회복되었습니다." << endl;

	this->hp += health;
	if (hp > maxhp)
	{
		hp = maxhp;
	}

	Sleep(1500);
}

void Character::AttackBoost(int attackBoost)
{
	cout << "캐릭터의 공격력이 " << attackBoost << "만큼 상승하였습니다." << endl;
	
	attackBonus += attackBoost;

	Sleep(1500);
}

std::shared_ptr<Item> Character::GetItem(int index) const {
	if (index < 1 || index > inventory.size()) {
		return nullptr;
	}
	auto it = std::next(inventory.begin(), index - 1);
	return it->first;
}

void Character::AddItem(std::shared_ptr<Item> item) {
	inventory[item]++;
}

bool Character::RemoveItem(std::shared_ptr<Item> item) {
	auto it = inventory.find(item);
	if (it != inventory.end()) {
		if (it->second > 1) {
			it->second--;
		}
		else {
			inventory.erase(it);
		}
		return true;
	}
	return false;
}

bool Character::HasItems() const {
	return !inventory.empty();
}

size_t Character::InventorySize() const {
	return inventory.size();
}

int Character::GetItemQuantity(std::shared_ptr<Item> item) const {
	auto it = inventory.find(item);
	return (it != inventory.end()) ? it->second : 0;
}

void Character::DisplayStatus() const {
	std::cout << "\n===== " << name << "의 상태 =====\n";
	std::cout << "체력: " << hp << "/" << maxhp << "\n";
	std::cout << "마나: " << mp << "/" << maxmp << "\n";
	std::cout << "공격력: " << attack << "\n";
	std::cout << "골드: " << gold << "\n";

	Sleep(3000);
}

void Character::SpendGold(int amount) {
	SetGold(GetGold() - amount);
}

void Character::EarnGold(int amount) {
	SetGold(GetGold() + amount);
}

// 스킬관련 ===========================================================================================

void Character::PrintSkillList()
{
	cout << "[ " << name << " ] 님이 현재 보유하고 있는 스킬목록 입니다." << endl;
	int index = 1;
	for (const auto& item : skillInventory)
	{
		cout << "[ " << index << " ] " << item->GetSkillName() << " / 데미지: " << item->GetDamage() << " / 소비마나: " << item->GetMp() << endl;
		index++;
	}
}

void Character::TakeSkill(unique_ptr<Skill> skill)
{
	cout << "[ " << name << " ] 님이 " << skill->GetSkillName() << "스킬을 얻었습니다!" << endl;

	if (skillInventory.size() >= 3) {
		cout << "더이상 스킬을 얻을 수 없습니다." << endl;
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
			cout << "현재 사용할 수 있는 스킬이 없습니다." << endl;
			Sleep(1000);

			return -1;
		}

		PrintSkillList();
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
				cout << "스킬에 필요한 마나가 부족합니다." << endl;
				break;
			}

			damage = skill->GetDamage() + static_cast<int>(skill->GetDamage() * skillEnhancement / 100);
			cout << "[ " << name << " ] 님의 " << skill->GetSkillName() << "!" << endl;
			mp -= skill->GetMp();

			break;
		}
		else
		{
			cout << "스킬이 존재하지 않습니다." << endl;
		}
	}

	return damage;
}
