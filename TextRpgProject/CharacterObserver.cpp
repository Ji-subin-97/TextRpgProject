#include "CharacterObserver.h"
#include "CharacterManager.h"

void CharacterManagerSystem::LevelUpEvent()
{
	CharacterManager* charManager = CharacterManager::GetInstance();
	Character* character = Character::GetInstance();

	if (character != nullptr && charManager != nullptr)
	{
		// 캐릭터 5Lv마다 스킬랜덤 얻기
		if (character->GetLevel() % 5 == 0)
		{
			charManager->CharacterGetSkill();
		}

		charManager->SetCharacterStatAfterLevelUp();
	}
}