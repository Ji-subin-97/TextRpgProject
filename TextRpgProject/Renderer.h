#pragma once

#include <vector>
#include "SingleTon.h"
#include "UIStruct.h"
#include "Object.h"
#include "Container.h"
#include "TextBox.h"
#include "InputBox.h"
#include "LogBox.h"
#include <memory>

using namespace std;

class Renderer : public SingleTon<Renderer>
{
	shared_ptr<Container> rootContainer = make_shared<Container>();
	InputBox* inputBox = nullptr;
	LogBox* logBox = nullptr;
	Pos appSize = {0,0};
private:
	friend class SingleTon<Renderer>;
	Renderer();
	void DrawObject(shared_ptr<Object> object);
	void DrawObject(Object* object);
	void ClearObject(shared_ptr<Object> object);
	void InitIOBox(Pos size);
	void AddObject(shared_ptr<Object> object);
public:
	//�ܼ־� ������
	void SetAppSize(int width, int height);
	void SetAppSize(Pos size);
	Pos GetAppSize() const;
	vector<shared_ptr<Object>> GetObjects() const;
	shared_ptr<Container> GetRootContainer() const;
	//GameMap Ŭ�������� ��� ��� SelectMap(GameMap::Index())
	void SelectMap(shared_ptr<Container> map);
	void Clear();
	void ClearAll();
	// textBox ���� �����ؼ� ������
	void EditText(int id, const string& text);
	void EditText(int id, int value);
	void ExpandText(int id, int width, int height);
	void EditTextColor(int id, RGB color);
	void SetTextBackgroundColor(int id, RGB color, int width);
	// object �����ؼ� ������
	void EditObjectColor(int id, RGB color);
	//������ GameMap ������
	void Render();
	//��ǲ/�α� �ڽ����� ��� ������
	void RenderAll();
	void DeleteInstanceAll();
};

