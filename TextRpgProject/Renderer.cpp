#include "Renderer.h"
#include "Cursor.h"
#include <string>
#include <iostream>
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN 
#include <Windows.h>
#include "Util.h"
#include "GameMap.h"

using namespace std;



void Renderer::SetAppSize(int width, int height)
{
    appSize = Pos(width, height);
}

void Renderer::SetAppSize(Pos size)
{
    appSize = size;
}

Pos Renderer::GetAppSize() const
{
    return rootContainer->GetSize();
}

void Renderer::AddObject(Object* object)
{
    rootContainer->AddObject(object);
}
vector<Object*> Renderer::GetObjects() const
{
    return rootContainer->GetChildren();
}
Container* Renderer::GetRootContainer() const
{
    return rootContainer;
}
void Renderer::SelectMap(Container* map)
{
    Clear();
    rootContainer = map;
    rootContainer->SetSize(appSize);
    this->Render();
}
void Renderer::Clear()
{
    if (rootContainer == nullptr) return;

    for (Object* object : rootContainer->GetChildren())
    {
        ClearObject(object);
    }

    delete rootContainer;
}
Renderer::Renderer()
{
    Pos size = Util::GetConsoleWindowSize();
    size.Y -= 13;
    this->SetAppSize(size);
    this->InitIOBox(size);
    this->DrawObject(this->inputBox);
    this->DrawObject(this->logBox);
}
void Renderer::DrawObject(Object* object)
{
    Pos pos = object->GetPos();
    RGB color = object->GetColor();
    Cursor::SetTextColor(color);
    for (const string& line : object->GetBody())
    {
        Cursor::SetPosition(pos);
        cout << line;
        pos.Y++;
    }
    Cursor::ResetAllStyle();
}
void Renderer::ClearObject(Object* object)
{
    Pos pos = object->GetPos();
    for (const string& line : object->GetBody())
    {
        Cursor::SetPosition(pos);
        cout << string(line.size(), ' '); // ºó ¹®ÀÚ¿­·Î µ¤¾î¾²±â
        pos.Y++;
    }
}
void Renderer::InitIOBox(Pos size)
{
    this->inputBox = InputBox::GetInstance();
    this->logBox = LogBox::GetInstance();
    Pos boxSize = size;
    int start = boxSize.Y + 1;
    boxSize.Y = 3;
    this->inputBox->SetSize(boxSize);
    this->inputBox->SetPos(1, start);
    start += 3;
    boxSize.Y = 10;
    this->logBox->SetSize(boxSize);
    this->logBox->SetPos(1, start);
}
void Renderer::Render()
{
    for (Object* object : rootContainer->GetChildren()) {
        DrawObject(object);
    }
}