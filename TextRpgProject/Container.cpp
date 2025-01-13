#include "Container.h"

void Container::AddBorder()
{
    vector<string> body;
    int height = this->GetSize().Y;

    body.push_back(MakeLine(LineType::top));
    for (int i = 0; i < height - 2; i++) {
        body.push_back(MakeLine(LineType::middle));
    }
    body.push_back(MakeLine(LineType::bottom));

    int text_index = height % 2 == 0 ? (height / 2) - 1 : height / 2;
    //body[text_index] = MakeLine(_text);

    this->SetBody(body);
}

Container::Container()
{
    //Setbody();
}
Container::Container(Pos pos)
{
    this->SetPos(pos);
}
void Container::AddObject(Object* object)
{
    object->SetParant(this);
    children.push_back(object);
    // 컨테이너에 오브젝트를 추가하면서, 오브젝트를 컨테이너에 맞게 수정
    Pos pos = this->GetPos();
    object->move(pos);
    object->SetOverlap(this->GetOverlap());
}

vector<Object*> Container::GetChildren() const
{
    return this->children;
}

void Container::SetPos(Pos pos)
{
    Pos delta = pos - this->GetPos();
    for (Object* child : children)
    {
        child->move(delta);
    }
}

void Container::SetPos(int x, int y)
{
    SetPos(Pos(x, y));
}
