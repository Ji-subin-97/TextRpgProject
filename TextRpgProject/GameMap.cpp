#include "GameMap.h"
#include "TextBox.h"

Container* GameMap::index()
{
    Container* root = new Container();

    TextBox* title = new TextBox("TextRPG");
    title->SetPos(40, 5);
    root->AddObject(title);

    Container* menuContainer = new Container({ 40, 10 });
    menuContainer->SetSize(12, 30);
    TextBox* start = new TextBox("����");
    TextBox* end = new TextBox("����");
    end->move(10, 10);
    menuContainer->AddObject(start);
    menuContainer->AddObject(end);
    root->AddObject(menuContainer);

    return root;
}
