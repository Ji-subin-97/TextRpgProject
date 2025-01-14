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
	//�ܼ־� ������
	void SetAppSize(int width, int height);
	void SetAppSize(Pos size);
	Pos GetAppSize() const;
	vector<Object*> GetObjects() const;
	Container* GetRootContainer() const;
	//GameMap Ŭ�������� ��� ��� SelectMap(GameMap::Index())
	void SelectMap(Container* map);
	void Clear();
	//������ GameMap ������
	void Render();
};

