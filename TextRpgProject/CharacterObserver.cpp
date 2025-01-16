#include "CharacterObserver.h"
#include "CharacterManager.h"

void CharacterManagerSystem::LevelUpEvent()
{
	CharacterManager* charManager = CharacterManager::GetInstance();
	Character* character = Character::GetInstance();

	if (character != nullptr && charManager != nullptr)
	{
		// ĳ���� 3Lv���� ��ų���� ���
		if (character->GetLevel() % 3 == 0)
		{
			charManager->CharacterGetSkill();
		}

		charManager->SetCharacterStatAfterLevelUp();
	}
}