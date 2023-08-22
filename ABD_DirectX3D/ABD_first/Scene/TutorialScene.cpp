#include "Framework.h"
#include "TutorialScene.h"



TutorialScene::TutorialScene()
{ // �ʱ�ȭ

    cube = new Cube();

}

TutorialScene::~TutorialScene()
{
   
    delete cube;
}

void TutorialScene::Update()
{
    cube->Update();
}

void TutorialScene::PreRender()
{
    cube->Debug();

}

void TutorialScene::Render()
{
   
    cube->Render();
  
}

void TutorialScene::PostRender()
{

}
