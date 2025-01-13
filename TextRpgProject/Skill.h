#pragma once
#include <string>

enum SkillType
{
	AD,
	AP
};

class Skill
{
public:
	virtual ~Skill() = default;
	virtual const std::string& GetSkillName() const = 0;
	virtual SkillType GetSkillType() const = 0;
	virtual int GetDamage() const = 0;
	virtual int GetMp() const = 0;
};

class FireBall : public Skill
{
private:
	std::string name;
	SkillType skillType;
	int damage;
	int mp;
public:
	FireBall();

	const std::string& GetSkillName() const;
	SkillType GetSkillType() const;
	int GetDamage() const;
	int GetMp() const;
};

class IceStorm : public Skill
{
private:
	std::string name;
	SkillType skillType;
	int damage;
	int mp;
public:
	IceStorm();

	const std::string& GetSkillName() const;
	SkillType GetSkillType() const;
	int GetDamage() const;
	int GetMp() const;
};

class Bomb : public Skill
{
private:
	std::string name;
	SkillType skillType;
	int damage;
	int mp;
public:
	Bomb();

	const std::string& GetSkillName() const;
	SkillType GetSkillType() const;
	int GetDamage() const;
	int GetMp() const;
};

class Meteor : public Skill
{
private:
	std::string name;
	SkillType skillType;
	int damage;
	int mp;
public:
	Meteor();

	const std::string& GetSkillName() const;
	SkillType GetSkillType() const;
	int GetDamage() const;
	int GetMp() const;
};

class Sparata : public Skill
{
private:
	std::string name;
	SkillType skillType;
	int damage;
	int mp;
public:
	Sparata();

	const std::string& GetSkillName() const;
	SkillType GetSkillType() const;
	int GetDamage() const;
	int GetMp() const;
};