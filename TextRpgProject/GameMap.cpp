#include "GameMap.h"
#include "TextBox.h"
#include "LogBox.h"
#include "InputBox.h"

Container* GameMap::index()
{
    Container* root = new Container();

    TextBox* title = new TextBox("TextRPG");
    title->SetPos(40, 5);
    title->SetSize(30, 3);
    title->ExpendHeight(1);
    root->AddObject(title);

    return root;
}

Container* GameMap::selectStat()
{
    Container* root = new Container();

    TextBox* hpTitle = new TextBox(" HP  ");
    TextBox* mpTitle = new TextBox(" MP  ");
    mpTitle->move(0, 2);
    TextBox* strTitle = new TextBox(" STR ");
    strTitle->move(0, 4);
    TextBox* dexTitle = new TextBox(" DEX ");
    dexTitle->move(0, 6);
    TextBox* intTitle = new TextBox(" INT ");
    intTitle->move(0, 8);
    TextBox* lukTitle = new TextBox(" LUK ");
    lukTitle->move(0, 10);
    TextBox* hpBody = new TextBox("        ");
    hpBody->move(6, 0);
    TextBox* mpBody = new TextBox("        ");
    mpBody->move(6, 2);
    TextBox* strBody = new TextBox("        ");
    strBody->move(6, 4);
    TextBox* dexBody = new TextBox("        ");
    dexBody->move(6, 6);
    TextBox* intBody = new TextBox("        ");
    intBody->move(6, 8);
    TextBox* lukBody = new TextBox("        ");
    lukBody->move(6, 10);
    hpBody->SetId(11);
    mpBody->SetId(12);
    strBody->SetId(13);
    dexBody->SetId(14);
    intBody->SetId(15);
    lukBody->SetId(16);

    root->AddObject({ 
        hpTitle, mpTitle, strTitle, dexTitle, intTitle, lukTitle,
        hpBody, mpBody, strBody, dexBody, intBody, lukBody
     });

    return root;;
}
