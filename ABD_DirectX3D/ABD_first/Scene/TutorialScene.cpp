#include "Framework.h"
#include "TutorialScene.h"



TutorialScene::TutorialScene()
{ // ÃÊ±âÈ­

    cube1 = new Cube(RED);
    cube2 = new Cube(BLUE);

    cube2->translation.x = 3;

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

    cube1->rotation.y += 0.0001f;
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
