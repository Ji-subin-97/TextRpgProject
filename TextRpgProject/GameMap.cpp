#include "GameMap.h"
#include "TextBox.h"
#include "LogBox.h"
#include "InputBox.h"

shared_ptr<Container> GameMap::Index()
{
    shared_ptr<Container> root = make_shared<Container>();

    shared_ptr<Object> title = make_shared<Object>();
    // 아스키 글자 소스 https://patorjk.com/software/taag/#p=display&f=Blocks&t=text%20rpg
    title->LoadFromTxt("title");
    title->SetColor(0, 255, 0);
    title->SetPos(12, 5);
    root->AddObject(title);

    return root;
}

shared_ptr<Container> GameMap::SelectStat()
{
    shared_ptr<Container> root = make_shared<Container>();

    shared_ptr<TextBox> hpTitle = make_shared<TextBox>(" HP   ");
    shared_ptr<TextBox> mpTitle = make_shared<TextBox>(" MP   ");
    shared_ptr<TextBox> strTitle = make_shared<TextBox>(" STR  ");
    shared_ptr<TextBox> dexTitle = make_shared<TextBox>(" DEX  ");
    shared_ptr<TextBox> intTitle = make_shared<TextBox>(" INT  ");
    shared_ptr<TextBox> lukTitle = make_shared<TextBox>(" LUK  ");
    mpTitle->move(0, 2);
    strTitle->move(0, 4);
    dexTitle->move(0, 6);
    intTitle->move(0, 8);
    lukTitle->move(0, 10);
    shared_ptr<TextBox> hpBody = make_shared<TextBox>("       ");
    shared_ptr<TextBox> mpBody = make_shared<TextBox>("       ");
    shared_ptr<TextBox> strBody = make_shared<TextBox>("       ");
    shared_ptr<TextBox> dexBody = make_shared<TextBox>("       ");
    shared_ptr<TextBox> intBody = make_shared<TextBox>("       ");
    shared_ptr<TextBox> lukBody = make_shared<TextBox>("       ");
    hpBody->move(6, 0);
    mpBody->move(6, 2);
    strBody->move(6, 4);
    dexBody->move(6, 6);
    intBody->move(6, 8);
    lukBody->move(6, 10);
    hpBody->SetId(11);
    mpBody->SetId(12);
    strBody->SetId(13);
    dexBody->SetId(14);
    intBody->SetId(15);
    lukBody->SetId(16);
    shared_ptr<TextBox> characterTitle = make_shared<TextBox>(" 이름 ");
    shared_ptr<TextBox> characterName = make_shared<TextBox>();
    characterTitle->move(20, 0);
    characterName->move(27, 0);
    characterName->SetId(20);

    root->AddObject
    ({ 
        hpTitle, mpTitle, strTitle, dexTitle, intTitle, lukTitle,
        hpBody, mpBody, strBody, dexBody, intBody, lukBody,
        characterTitle, characterName
     });

    return root;;
}

shared_ptr<Container> GameMap::Main()
{
    shared_ptr<Container> root = make_shared<Container>();

    shared_ptr<Object> battleIcon = make_shared<Object>();
    shared_ptr<Object> statIcon = make_shared<Object>();
    shared_ptr<Object> inventoryIcon = make_shared<Object>();
    shared_ptr<Object> storeIcon = make_shared<Object>();
    shared_ptr<Object> exitIcon = make_shared<Object>();
    battleIcon->LoadFromTxt("sword");
    statIcon->LoadFromTxt("head");
    inventoryIcon->LoadFromTxt("potion");
    storeIcon->LoadFromTxt("store");
    exitIcon->LoadFromTxt("power_button");
    battleIcon->move(13, 1);
    statIcon->move(30, 1);
    inventoryIcon->move(53, 4);
    storeIcon->move(70, 2);
    exitIcon->move(90, 3);
    shared_ptr<TextBox> battleTitle = make_shared<TextBox>("  1. 전투  ");
    shared_ptr<TextBox> statTitle = make_shared<TextBox>("  2. 스탯  ");
    shared_ptr<TextBox> inventoryTitle = make_shared<TextBox>("  3. 물약  ");
    shared_ptr<TextBox> storeTitle = make_shared<TextBox>("  4. 상점  ");
    shared_ptr<TextBox> exitTitle = make_shared<TextBox>("  5. 종료  ");
    battleTitle->move(10, 10);
    statTitle->move(30, 10);
    inventoryTitle->move(50, 10);
    storeTitle->move(70, 10);
    exitTitle->move(90, 10);

    root->AddObject
    ({
        battleIcon, statIcon, inventoryIcon, storeIcon, exitIcon,
        battleTitle, statTitle, inventoryTitle, storeTitle, exitTitle
     });

    return root;
}


shared_ptr<Container> GameMap::SelectBattle()
{
    shared_ptr<Container> root = make_shared<Container>();


    shared_ptr<TextBox> levelTitle = make_shared<TextBox>(" 레벨 ");
    shared_ptr<TextBox> hpTitle = make_shared<TextBox>(" HP   ");
    shared_ptr<TextBox> mpTitle = make_shared<TextBox>(" MP   ");
    shared_ptr<TextBox> strTitle = make_shared<TextBox>(" STR  ");
    shared_ptr<TextBox> dexTitle = make_shared<TextBox>(" DEX  ");
    shared_ptr<TextBox> intTitle = make_shared<TextBox>(" INT  ");
    shared_ptr<TextBox> lukTitle = make_shared<TextBox>(" LUK  ");
    shared_ptr<TextBox> attackTitle = make_shared<TextBox>(" 공격력             ");
    shared_ptr<TextBox> defenseTitle = make_shared<TextBox>(" 방어력             ");
    shared_ptr<TextBox> accuracyTitle = make_shared<TextBox>(" 명중률             ");
    shared_ptr<TextBox> skilldamageTitle = make_shared<TextBox>(" 스킬데미지증가율 ");
    shared_ptr<TextBox> criticalTitle = make_shared<TextBox>(" 치명타율         ");
    shared_ptr<TextBox> expTitle = make_shared<TextBox>(" 경험치             ");
    shared_ptr<TextBox> goldTitle = make_shared<TextBox>(" 골드                ");
    levelTitle->move(0, 0);
    hpTitle->move(0, 2);
    mpTitle->move(0, 4);
    strTitle->move(0, 6);
    dexTitle->move(0, 8);
    intTitle->move(0, 10);
    lukTitle->move(0, 12);
    attackTitle->move(15, 0);
    defenseTitle->move(15, 2);
    accuracyTitle->move(15, 4);
    skilldamageTitle->move(15, 6);
    criticalTitle->move(15, 8);
    expTitle->move(15, 10);
    goldTitle->move(15, 12);
    shared_ptr<TextBox> levelBody = make_shared<TextBox>("  0    ");
    shared_ptr<TextBox> hpBody = make_shared<TextBox>("  0    ");
    shared_ptr<TextBox> mpBody = make_shared<TextBox>("  0    ");
    shared_ptr<TextBox> attackBody = make_shared<TextBox>("  0    ");
    shared_ptr<TextBox> strBody = make_shared<TextBox>("  0    ");
    shared_ptr<TextBox> dexBody = make_shared<TextBox>("  0    ");
    shared_ptr<TextBox> intBody = make_shared<TextBox>("  0    ");
    shared_ptr<TextBox> lukBody = make_shared<TextBox>("  0    ");
    shared_ptr<TextBox> defenseBody = make_shared<TextBox>("  0    ");
    shared_ptr<TextBox> accuracyBody = make_shared<TextBox>("  0    ");
    shared_ptr<TextBox> skilldamageBody = make_shared<TextBox>("  0    ");
    shared_ptr<TextBox> criticalBody = make_shared<TextBox>("  0    ");
    shared_ptr<TextBox> expBody = make_shared<TextBox>("  0    ");
    shared_ptr<TextBox> goldBody = make_shared<TextBox>("  0    ");
    levelBody->move(7, 0);
    hpBody->move(7, 2);
    mpBody->move(7, 4);
    strBody->move(7, 6);
    dexBody->move(7, 8);
    intBody->move(7, 10);
    lukBody->move(7, 12);
    attackBody->move(34, 0);
    defenseBody->move(34, 2);
    accuracyBody->move(34, 4);
    skilldamageBody->move(34, 6);
    criticalBody->move(34, 8);
    expBody->move(34, 10);
    goldBody->move(34, 12);
    levelBody->SetId(21);
    hpBody->SetId(22);
    mpBody->SetId(23);
    strBody->SetId(24);
    dexBody->SetId(25);
    intBody->SetId(26);
    lukBody->SetId(27);
    attackBody->SetId(31);
    defenseBody->SetId(32);
    accuracyBody->SetId(33);
    skilldamageBody->SetId(34);
    criticalBody->SetId(35);
    expBody->SetId(36);
    goldBody->SetId(37);
    shared_ptr<TextBox> name = make_shared<TextBox>(" ");
    name->move(65, 4);
    name->SetId(40);
    shared_ptr<Object> characterIcon = make_shared<Object>();
    characterIcon->LoadFromTxt("head");
    characterIcon->move(48, 6);
    shared_ptr<TextBox> hpBar = make_shared<TextBox>();
    shared_ptr<TextBox> mpBar = make_shared<TextBox>();
    shared_ptr<TextBox> expBar = make_shared<TextBox>();
    hpBar->move(65, 8);
    mpBar->move(65, 10);
    expBar->move(65, 12);
    hpBar->SetSize(52, 3);
    mpBar->SetSize(52, 3);
    expBar->SetSize(52, 3);
    hpBar->SetId(51);
    mpBar->SetId(52);
    expBar->SetId(53);

    root->AddObject
    ({
        levelTitle, hpTitle, mpTitle, strTitle, dexTitle, intTitle, lukTitle,
        attackTitle, defenseTitle, accuracyTitle, skilldamageTitle, criticalTitle, expTitle, goldTitle,
        levelBody, hpBody, mpBody, strBody, dexBody, intBody, lukBody,
        attackBody, defenseBody, accuracyBody, skilldamageBody, criticalBody, expBody, goldBody,
        name, characterIcon, hpBar, mpBar, expBar
    });

    return root;
}

shared_ptr<Container> GameMap::Battle()
{
    shared_ptr<Container> root = make_shared<Container>();

    
    shared_ptr<Object> characterIcon = make_shared<Object>();
    characterIcon->LoadFromTxt("head");
    characterIcon->move(0, -1);
    shared_ptr<TextBox> hpBar = make_shared<TextBox>();
    shared_ptr<TextBox> mpBar = make_shared<TextBox>();
    shared_ptr<TextBox> expBar = make_shared<TextBox>();
    hpBar->move(15, 0);
    mpBar->move(15, 2);
    expBar->move(15, 4);
    hpBar->SetSize(82, 3);
    mpBar->SetSize(82, 3);
    expBar->SetSize(82, 3);
    hpBar->SetId(21);
    mpBar->SetId(22);
    expBar->SetId(23);
    shared_ptr<TextBox> characterName = make_shared<TextBox>(" ");
    shared_ptr<TextBox> enemyName = make_shared<TextBox>(" ");
    /*
    shared_ptr<Object> characterBody = make_shared<Object>();
    shared_ptr<Object> enemyBody = make_shared<Object>();
    characterBody->LoadFromTxt("character");
    enemyBody->LoadFromTxt("monster");
    characterBody->move(13, 2);
    enemyBody->move(13, 2);
    characterBody->SetId(32);
    enemyBody->SetId(42);
    */
    characterName->move(15, 6);
    enemyName->move(15, 11);
    characterName->SetId(31);
    enemyName->SetId(41);
    shared_ptr<TextBox> enemyHpBar = make_shared<TextBox>(" ");
    shared_ptr<Object> enemyIcon = make_shared<Object>();
    enemyHpBar->SetSize(82, 3);
    enemyIcon->LoadFromTxt("monster_head");
    enemyHpBar->move(15, 13);
    enemyIcon->move(0, 8);
    enemyHpBar->SetId(51);
    characterIcon->SetId(61);
    enemyIcon->SetId(62);

    root->AddObject
    ({
        characterIcon, hpBar, mpBar, expBar,
        characterName, enemyName, enemyHpBar, enemyIcon
    });

    return root;
}
