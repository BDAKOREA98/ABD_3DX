#include "Framework.h"
#include "TextureScene.h"

TextureScene::TextureScene()
{
	quad = new Quad({2,1});

}

TextureScene::~TextureScene()
{
	delete quad;
}

void TextureScene::Update()
{
}

void TextureScene::PreRender()
{
}

void TextureScene::Render()
{
	quad->Render();
}

void TextureScene::PostRender()
{
}
