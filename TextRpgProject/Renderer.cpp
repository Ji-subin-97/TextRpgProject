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

void Renderer::AddObject(shared_ptr<Object> object)
{
    rootContainer->AddObject(object);
}
vector<shared_ptr<Object>> Renderer::GetObjects() const
{
    return rootContainer->GetChildren();
}
shared_ptr<Container> Renderer::GetRootContainer() const
{
    return rootContainer;
}
void Renderer::SelectMap(shared_ptr<Container> map)
{
    logBox->Clear();
    Cursor::ClearScreen();
    rootContainer = map;
    rootContainer->SetSize(appSize);
    this->RenderAll();
}
void Renderer::Clear()
{
    if (rootContainer == nullptr) return;

    for (shared_ptr<Object> object : rootContainer->GetChildren())
    {
        ClearObject(object);
    }
}
void Renderer::ClearAll()
{
    Cursor::ClearScreen();
}
void Renderer::EditText(int id, const string& text)
{
    shared_ptr<TextBox> textBox = rootContainer->FindObject<TextBox>(id);
    if (textBox == nullptr) return;

    textBox->SetText(text);
    this->DrawObject(textBox);
}
void Renderer::EditText(int id, int value)
{
    this->EditText(id, to_string(value));
}
void Renderer::ExpandText(int id, int width, int height)
{
    shared_ptr<TextBox> textBox = rootContainer->FindObject<TextBox>(id);
    if (textBox == nullptr) return;

    textBox->ExpandWidth(width);
    textBox->ExpandHeight(height);
    this->DrawObject(textBox);
}
void Renderer::EditTextColor(int id, RGB color)
{
    shared_ptr<TextBox> textBox = rootContainer->FindObject<TextBox>(id);
    if (textBox == nullptr) return;

    textBox->SetColor(color);
    this->DrawObject(textBox);
}
void Renderer::SetTextBackgroundColor(int id, RGB color, int width)
{
    shared_ptr<TextBox> textBox = rootContainer->FindObject<TextBox>(id);
    if (textBox == nullptr) return;
    this->DrawObject(textBox);

    string text = textBox->GetText();
    int textLength = text.length();
    int boxWidth = textBox->GetSize().X - 2;
    int paddingLeft = (boxWidth - textLength) / 2;
    int paddingRight = boxWidth - paddingLeft - textLength;
    text = string(paddingLeft, ' ') + text + string(paddingRight, ' ');

    int length = width > boxWidth ? boxWidth : width;

    Cursor::SetPosition(textBox->GetPos() + Pos(1, 1));
    Cursor::SetBackgroundColor(color);
    for (int i = 0; i < length; i++) { cout << text[i]; }

    Cursor::ResetBackgroundColor();
    for (int i = length; i < text.length(); i++) { cout << text[i]; }

}
void Renderer::EditObjectColor(int id, RGB color)
{
    shared_ptr<Object> textBox = rootContainer->FindObject<Object>(id);
    if (textBox == nullptr) return;

    textBox->SetColor(color);
    this->DrawObject(textBox);
}
Renderer::Renderer()
{
    Cursor::HideCursor();
    Pos size = Util::GetConsoleWindowSize();
    size.Y -= 13;
    this->SetAppSize(size);
    this->InitIOBox(size);
    this->DrawObject(this->inputBox);
    this->DrawObject(this->logBox);
}
void Renderer::DrawObject(shared_ptr<Object> object)
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
void Renderer::ClearObject(shared_ptr<Object> object)
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
    for (auto& object : rootContainer->GetChildren()) {
        DrawObject(object);
    }
}

void Renderer::RenderAll()
{
    this->ClearAll();
    this->Render();
    this->DrawObject(this->inputBox);
    this->DrawObject(this->logBox);
}

void Renderer::DeleteInstanceAll()
{
    inputBox->DeleteInstance();
    logBox->DeleteInstance();
    DeleteInstance();

}
