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
	//콘솔앱 사이즈
	void SetAppSize(int width, int height);
	void SetAppSize(Pos size);
	Pos GetAppSize() const;
	vector<shared_ptr<Object>> GetObjects() const;
	shared_ptr<Container> GetRootContainer() const;
	//GameMap 클래스에서 골라 사용 SelectMap(GameMap::Index())
	void SelectMap(shared_ptr<Container> map);
	void Clear();
	void ClearAll();
	// textBox 내용 변경해서 렌더링
	void EditText(int id, const string& text);
	void EditText(int id, int value);
	void ExpandText(int id, int width, int height);
	void EditTextColor(int id, RGB color);
	void SetTextBackgroundColor(int id, RGB color, int width);
	// object 변경해서 렌더링
	void EditObjectColor(int id, RGB color);
	//가져온 GameMap 렌더링
	void Render();
	//인풋/로그 박스까지 모두 렌더링
	void RenderAll();
	void DeleteInstanceAll();
};

