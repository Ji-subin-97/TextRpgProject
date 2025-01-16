#include "CharacterObserver.h"
#include "CharacterManager.h"

void CharacterManagerSystem::LevelUpEvent()
{
	CharacterManager* charManager = CharacterManager::GetInstance();
	Character* character = Character::GetInstance();

	if (character != nullptr && charManager != nullptr)
	{
		// 캐릭터 3Lv마다 스킬랜덤 얻기
		if (character->GetLevel() % 3 == 0)
		{
			charManager->CharacterGetSkill();
		}

		charManager->SetCharacterStatAfterLevelUp();
	}
}