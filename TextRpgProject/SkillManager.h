#pragma once
#include <memory>
#include "SingleTon.h"
#include "Skill.h"

class SkillManager : public SingleTon<SkillManager>
{
private:
	SkillManager() = default;
	~SkillManager() = default;

	friend class SingleTon<SkillManager>;
public:
	std::unique_ptr<Skill> TakeSkillRandom();				// 스킬 복사본 얻기			
};