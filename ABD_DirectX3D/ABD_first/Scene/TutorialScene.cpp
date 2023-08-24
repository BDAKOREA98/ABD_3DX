#include "Framework.h"
#include "TutorialScene.h"



TutorialScene::TutorialScene()
{ // ÃÊ±âÈ­

    cube1 = new Cube(RED);
    cube2 = new Cube(BLUE);

   // cube2->translation.x = 3;

    cube2->SetParent(cube1);


    
}

TutorialScene::~TutorialScene()
{
   
    delete cube1;
    delete cube2;
}

void TutorialScene::Update()
{
    cube1->Update();
    cube2->Update();

//    cube1->rotation.y += 0.0001f;

    if (Key_PRESS(VK_LEFT))
    {
        cube1->translation += cube1->Left() * Time::Delta();
    }
    else if (Key_PRESS(VK_RIGHT))
    {
        cube1->translation += cube1->Right() * Time::Delta();
    }
    else if (Key_PRESS(VK_UP))
    {
        cube1->translation += cube1->Up() * Time::Delta();
    }
    else if (Key_PRESS(VK_DOWN))
    {
        cube1->translation += cube1->Down() * Time::Delta();
    }

    if (Key_PRESS('Q'))
    {
        cube1->rotation.z += Time::Delta();
    }
    if (Key_PRESS('E'))
    {
        cube1->rotation.z -= Time::Delta();
    }

    if (Key_PRESS('A'))
    {
        cube2->translation += cube2->Left() * Time::Delta();
    }                             
    if (Key_PRESS('D'))           
    {                             
        cube2->translation += cube2->Right() * Time::Delta();
    }

}

void TutorialScene::PreRender()
{
    cube1->Debug();
    cube2->Debug();

}

void TutorialScene::Render()
{
   
    cube1->Render();
    cube2->Render();
  
}

void TutorialScene::PostRender()
{

}
