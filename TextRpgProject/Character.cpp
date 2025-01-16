#include <iostream>
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN 
#include <Windows.h>
#include "Character.h"
#include "Random.h"

using namespace std;

// ĳ���� �ʱ�ȭ
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

// ������ ���
void Character::AddCharacterObserver(shared_ptr<CharacterObserver> observer)
{
	characterObservers.push_back(observer);
}

// �̺�Ʈ
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

// ĳ���� �ൿ
void Character::CharacterLevelUp()
{
	// ������ �� ����5++, ����1++ �� �Ŵ������� ĳ���ʹɷ�ġ ����
	level++;
	statStock += 5;

	NotifyLevelUpEvent();
}

int Character::CharacterAttack()
{
	// ���ݰ�� : ���� ���н� ������ 0, ���߽� (���ݷ� * 1.3(ġ��ŸȮ�� ����� 1.3��))
	int attack = this->attack + attackBonus;	// ������ ��� �߰������� ���ʽ����ݷ� �߰�.
	double accuracy = this->accuracy;
	double randomScope = GetDoubleToRandom(0.0, 100.0);

	if (randomScope > accuracy)
	{
		cout << "[ " << name << " ] ���� ������ ���������ϴ�!" << endl;
		Sleep(1000);
		return 0;
	}

	double criticalChance = this->criticalChance;
	randomScope = GetDoubleToRandom(0.0, 100.0);

	if (randomScope < criticalChance)
	{
		attack = static_cast<int>(attack * 1.3);
		cout << "[ " << name << " ] ���� ������ " << attack << "��ŭ ġ������ �������� �־����ϴ�!" << endl;
	}
	else {
		cout << "[ " << name << " ] ���� ������ " << attack << "��ŭ �������� �־����ϴ�!" << endl;
	}
	Sleep(1000);

	return attack;
}

void Character::TakeDamage(int damage)
{
	// ������ ���: HP - (������ - ���ذ�����) �� 0 �̸� X
	damage = damage - damageReduction < 0 ? 0 : damage - damageReduction;
	cout << "[ " << name << " ] ���� " << damage << "��ŭ �������� �Ծ����ϴ�!" << endl;
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

// �����۰���
void Character::PrintItemList()
{
	std::cout << "\n===== " << name << "�� �κ��丮 =====\n";
	int index = 1;
	for (const auto& pair : inventory) {
		const auto& item = pair.first;
		int quantity = pair.second;
		std::cout << "[ " << index++ << " ] " << item->GetName()
			<< " (ü�� +" << item->GetHealthBoost()
			<< ", ���ݷ� +" << item->GetAttackBoost()
			<< ") x" << quantity << "��\n";
	}
}

int Character::UseItem()
{
	int choice = 0;

	while (true)
	{
		if (inventory.empty())
		{
			cout << "���� �����ϰ� �ִ� �������� �����ϴ�." << endl;
			Sleep(1500);
			break;
		}

		PrintItemList();
		cout << "[ 0 ] ������." << endl;
		cout << "����Ͻ� �������� �������ּ���." << endl;
		cout << "����: ";
		cin >> choice;

		if (cin.fail())
		{
			cout << "���ڸ� �Է°����մϴ�." << endl;
			cin.clear();
			cin.ignore();

			continue;
		}

		// ������ �������� -1 ����
		if (choice == 0)
		{
			return -1;
		}

		int attackBoost = 0;
		int healthBoost = 0;

		auto item = GetItem(choice);
		if (!item) {
			std::cout << "�߸��� ������ ��ȣ�Դϴ�.\n";
			continue;
		}
		else
		{
			attackBoost = item->GetAttackBoost();
			healthBoost = item->GetHealthBoost();

			cout << "[ " << name << " ] �� " << item->GetName() << "�������� ����Ͽ����ϴ�!" << endl;
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
	cout << "ĳ���Ͱ� " << health << "��ŭ ȸ���Ǿ����ϴ�." << endl;

	this->hp += health;
	if (hp > maxhp)
	{
		hp = maxhp;
	}

	Sleep(1500);
}

void Character::AttackBoost(int attackBoost)
{
	cout << "ĳ������ ���ݷ��� " << attackBoost << "��ŭ ����Ͽ����ϴ�." << endl;
	
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
	std::cout << "\n===== " << name << "�� ���� =====\n";
	std::cout << "ü��: " << hp << "/" << maxhp << "\n";
	std::cout << "����: " << mp << "/" << maxmp << "\n";
	std::cout << "���ݷ�: " << attack << "\n";
	std::cout << "���: " << gold << "\n";

	Sleep(3000);
}

void Character::SpendGold(int amount) {
	SetGold(GetGold() - amount);
}

void Character::EarnGold(int amount) {
	SetGold(GetGold() + amount);
}

// ��ų���� ===========================================================================================

void Character::PrintSkillList()
{
	cout << "[ " << name << " ] ���� ���� �����ϰ� �ִ� ��ų��� �Դϴ�." << endl;
	int index = 1;
	for (const auto& item : skillInventory)
	{
		cout << "[ " << index << " ] " << item->GetSkillName() << " / ������: " << item->GetDamage() << " / �Һ񸶳�: " << item->GetMp() << endl;
		index++;
	}
}

void Character::TakeSkill(unique_ptr<Skill> skill)
{
	cout << "[ " << name << " ] ���� " << skill->GetSkillName() << "��ų�� ������ϴ�!" << endl;

	if (skillInventory.size() >= 3) {
		cout << "���̻� ��ų�� ���� �� �����ϴ�." << endl;
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
		// ����� ��ų�� �������
		if (skillInventory.size() == 0)
		{
			cout << "���� ����� �� �ִ� ��ų�� �����ϴ�." << endl;
			Sleep(1000);

			return -1;
		}

		PrintSkillList();
		cout << "[ 0 ] ������." << endl;
		cout << "����Ͻ� ��ų�� �������ּ���." << endl;
		cout << "����: ";
		cin >> choice;

		if (cin.fail())
		{
			cout << "���ڸ� �Է°����մϴ�." << endl;
			cin.clear();
			cin.ignore();

			continue;
		}

		// ������ �������� -1 ����
		if (choice == 0)
		{
			return -1;
		}

		const unique_ptr<Skill>& skill = skillInventory[choice - 1];

		if (skill != nullptr)
		{
			// ��ų�Ҹ𸶳��� MP���� Ŭ�� ���Ұ�
			if (mp < skill->GetMp())
			{
				cout << "��ų�� �ʿ��� ������ �����մϴ�." << endl;
				break;
			}

			damage = skill->GetDamage() + static_cast<int>(skill->GetDamage() * skillEnhancement / 100);
			cout << "[ " << name << " ] ���� " << skill->GetSkillName() << "!" << endl;
			mp -= skill->GetMp();

			break;
		}
		else
		{
			cout << "��ų�� �������� �ʽ��ϴ�." << endl;
		}
	}

	return damage;
}
