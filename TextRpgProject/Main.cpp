#include <iostream>
#include "GameManager.h"
#include <string>
#include "Util.h"
#include "Renderer.h"
#include "Container.h"
#include "TextBox.h"
#include <windows.h>
#include "UIStruct.h"

using namespace std;

int main()
{
	//GameManager* gameManager = GameManager::GetInstance();
	//gameManager->StartGame();
	//gameManager->DeleteInstance();
	Renderer* r = Renderer::GetInstance();
	TextBox t("owo");
    //r->AddObject(&t);
	r->Render();

	return 0;
}