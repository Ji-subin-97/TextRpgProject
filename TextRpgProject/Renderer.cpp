#include "Renderer.h"
#include "Cursor.h"
#include <string>
#include <iostream>
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
void Renderer::SelectMap()
{
    rootContainer = GameMap::index();
    rootContainer->SetSize(appSize);
}
Renderer::Renderer()
{
    Pos size = Util::GetConsoleWindowSize();
    this->SetAppSize(size);
    this->InitLogBox();
    size.Y -= this->logBox->GetSize().Y;
    this->SelectMap();
}
void Renderer::DrawObject(Object* object)
{
    Pos pos = object->GetPos();
    RGB color = object->GetColor();
    Cursor::SetTextColor(color);
    for (const string& line : object->GetBody()) {
        Cursor::SetPosition(pos);
        cout << line;
        pos.Y++;
    }
    Cursor::ResetAllStyle();
}
void Renderer::InitLogBox()
{
    this->logBox = new TextBox();
    Pos size = this->appSize;
    int start = size.Y;
    size.Y /= 3;
    start -= size.Y;
    this->logBox->SetSize(size);
    this->logBox->SetPos(1, start);
}
#include <functional>

void Renderer::Render()
{
    // ��������� ��ü�� �������ϴ� �Լ�
    std::function<void(Object*)> renderObject = [&](Object* object) {
        Pos objectPos = object->GetPos();
        Pos objectSize = object->GetSize();
        Pos containerSize = rootContainer->GetSize();
        Pos containerPos = rootContainer->GetPos();

        // ��ü�� Container ���� ���� �ִ��� Ȯ��
        if (objectPos.X >= containerPos.X && objectPos.X + objectSize.X <= containerPos.X + containerSize.X &&
            objectPos.Y >= containerPos.Y && objectPos.Y + objectSize.Y <= containerPos.Y + containerSize.Y) {
            DrawObject(object);
        }

        // ��ü�� Container�� ���, �ڽ� ��ü�鵵 ������
        Container* container = dynamic_cast<Container*>(object);
        if (container) {
            for (Object* child : container->GetChildren()) {
                renderObject(child);
            }
        }
    };

    // rootContainer�� ��� �ڽ� ��ü�� ������
    for (Object* object : rootContainer->GetChildren()) {
        DrawObject(object);
    }
    this->DrawObject(this->logBox);
}