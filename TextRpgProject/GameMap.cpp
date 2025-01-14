#include "GameMap.h"
#include "TextBox.h"

Container* GameMap::index()
{
    Container* root = new Container();

    TextBox* title = new TextBox("TextRPG");
    title->SetPos(40, 5);
    title->SetSize(30, 3);
    title->ExpendHeight(1);
    root->AddObject(title);
    TextBox* start = new TextBox("시작");
    TextBox* end = new TextBox("종료");
    start->ExpendWidth(1);
    end->ExpendWidth(1);
    start->SetPos(40, 15);
    end->SetPos(62, 15);
    root->AddObject(start);
    root->AddObject(end);
    return root;
}
