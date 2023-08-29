#include "Framework.h"
#include "TextureScene.h"

TextureScene::TextureScene()
{
	cube = new TextureCube();
	cube->SetLabel("CUBE");
}

TextureScene::~TextureScene()
{
	delete cube;
	
}

void TextureScene::Update()
{
	
	cube->Update();
}

void TextureScene::PreRender()
{
}

void TextureScene::Render()
{
	cube->Render();
	
}

void TextureScene::PostRender()
{
	cube->Debug();
}
