#include "CharacterObserver.h"
#include "CharacterManager.h"

void CharacterManagerSystem::LevelUpEvent()
{
	CharacterManager* charManager = CharacterManager::GetInstance();
	Character* character = Character::GetInstance();

	if (character != nullptr && charManager != nullptr)
	{
		// ĳ���� 5Lv���� ��ų���� ���
		if (character->GetLevel() % 5 == 0)
		{
			charManager->CharacterGetSkill();
		}

		charManager->SetCharacterStatAfterLevelUp();
	}
}