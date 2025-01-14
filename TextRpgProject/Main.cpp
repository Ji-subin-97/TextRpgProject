#include <iostream>
#include "GameManager.h"
#include <string>
#include "Util.h"
#include "Renderer.h"
#include "Container.h"
#include "TextBox.h"
#include <windows.h>
#include "UIStruct.h"
#include "Cursor.h"
using namespace std;

int main()
{
	//GameManager* gameManager = GameManager::GetInstance();
	//gameManager->StartGame();
	//gameManager->DeleteInstance();
	Renderer* r = Renderer::GetInstance();
	r->Render();
	return 0;
}