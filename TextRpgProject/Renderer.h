#pragma once

#include <vector>
#include "SingleTon.h"
#include "UIStruct.h"
#include "Object.h"
#include "Container.h"
#include "TextBox.h"
#include "InputBox.h"
#include "LogBox.h"

using namespace std;

class Renderer : public SingleTon<Renderer>
{
	Container* rootContainer = nullptr;
	InputBox* inputBox = nullptr;
	TextBox* logBox = nullptr;
	Pos appSize = {0,0};
private:
	friend class SingleTon<Renderer>;
	Renderer();
	void DrawObject(Object* object);
	void ClearObject(Object* object);
	void InitIOBox(Pos size);
	void AddObject(Object* object);
public:
	//콘솔앱 사이즈
	void SetAppSize(int width, int height);
	void SetAppSize(Pos size);
	Pos GetAppSize() const;
	vector<Object*> GetObjects() const;
	Container* GetRootContainer() const;
	//GameMap 클래스에서 골라 사용 SelectMap(GameMap::Index())
	void SelectMap(Container* map);
	void Clear();
	//가져온 GameMap 렌더링
	void Render();
};

