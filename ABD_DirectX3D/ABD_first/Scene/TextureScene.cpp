#include "Framework.h"
#include "TextureScene.h"

TextureScene::TextureScene()
{
	cube = new TextureCube();
	cube->SetLabel("CUBE");

	CAMERA->translation = { 0, 3, -5 };

	cube2 = new Cube({ 1,0,0,1 });
	cube2->translation.x = 2;
	cube2->SetLabel("CUBE2");

}

TextureScene::~TextureScene()
{
	delete cube;
	delete cube2;
	
}

void TextureScene::Update()
{
	
	cube->Update();
	cube2->Update();

	if (KEY_PRESS('W'))
	{
		cube->rotation.x +=  0.0002f;
		cube2->rotation.x += 0.0002f;

	}

}

void TextureScene::PreRender()
{
}

void TextureScene::Render()
{
	cube->Render();
	cube2->Render();
	
}

void TextureScene::PostRender()
{
	cube->Debug();
	cube2->Debug();
}
