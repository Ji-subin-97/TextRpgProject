#include "Object.h"
#include "Util.h"

Object::Object()
{
}
Object::~Object()
{
}
void Object::LoadFromTxt(string path)
{
	vector<string> body = Util::ReadText(path);
	SetBody(body);
}
void Object::move(Pos value)
{
	this->SetPos(this->GetPos() + value);
}
void Object::move(int x, int y)
{
	move(Pos(x, y));
}
void Object::UpdateSize()
{
	int height = (int)body.size();
	int width = (int)Util::GetLongestStringSize(body);
	size = Pos(width, height);
}
void Object::UpdateSize(Pos _size)
{
	size = _size;
}
void Object::UpdateSize(int width, int height)
{
	size = Pos(width, height);
}
void Object::SetColor(RGB _color)
{
	color = _color;
}
void Object::SetColor(uInt8 r, uInt8 g, uInt8 b)
{
	color = RGB(r, g, b);
}
void Object::SetBody(vector<string>& _body) {
	body = _body;
	UpdateSize();
}
void Object::SetPos(Pos _pos)
{
	pos = _pos;
}
void Object::SetPos(int x, int y)
{
	pos = Pos(x, y);
}
void Object::SetId(int _id)
{
	id = _id;
}
//void Object::SetParant(Object* object)
//{
//	parent = object;
//}
void Object::SetOverlap(int value)
{
	overlap = value;
}
RGB Object::GetColor() const
{
	return color;
}
vector<string> Object::GetBody() const
{
	return body;
}
Pos Object::GetPos() const
{
	return pos;
}
Pos Object::GetSize() const
{
	return size;
}
int Object::GetId() const
{
	return id;
}
int Object::GetOverlap() const
{
	return overlap;
}
//Object* Object::GetParent() const
//{
//	return parent;
//}