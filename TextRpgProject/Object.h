#pragma once

#include <string>
#include <vector>
#include "UIStruct.h"

using namespace std;

class Object
{
	vector<string> body;
	RGB color = { 255, 255, 255 };
	Pos pos = { 1, 1 }; // (1,1) 이 시작점
	Pos size = { 0, 0 };
	int overlap = 0;
	//uInt8 depth = 0;
	int id = 0;
	Object* parent = nullptr;
protected:
	void UpdateSize();
	void UpdateSize(Pos _size);
	void UpdateSize(int width, int height);
public:
	Object();
	virtual ~Object();
	//virtual void LoadFromTxt(string path) = 0;
	void move(Pos value);
	void move(int x, int y);
	void SetColor(RGB _color);
	void SetColor(uInt8 r, uInt8 g, uInt8 b);
	void SetBody(vector<string>& _body);
	virtual void SetPos(Pos _pos);
	virtual void SetPos(int x, int y);
	void SetId(int _id);
	void SetParant(Object* object);
	void SetOverlap(int value);
	RGB GetColor() const;
	vector<string> GetBody() const;
	Pos GetPos() const;
	Pos GetSize() const;
	int GetId() const;
	int GetOverlap() const;
	Object* GetParent() const;
};

