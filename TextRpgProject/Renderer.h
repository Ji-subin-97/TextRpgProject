#pragma once

#include <vector>
#include "Singleton.h"
#include "UIStruct.h"
#include "Object.h"
#include "Container.h"
#include "TextBox.h"

using namespace std;

class Renderer : public Singleton<Renderer>
{
	Container* rootContainer = nullptr;
	TextBox* logBox = nullptr;
	Pos appSize = {0,0};
private:
	friend class Singleton<Renderer>;
	Renderer();
	void DrawObject(Object* object);
	void InitLogBox();
public:
	void SetAppSize(int width, int height);
	void SetAppSize(Pos size);
	Pos GetAppSize() const;
	void AddObject(Object* object);
	void SelectMap();
	void Render();
};

