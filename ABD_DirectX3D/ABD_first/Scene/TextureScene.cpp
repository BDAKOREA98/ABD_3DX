#include "Framework.h"
#include "TextureScene.h"

TextureScene::TextureScene()
{
	cube = new TextureCube();
	cube->SetLabel("TextureCUBE");

	CAMERA->translation = { 0, 3, -5 };

	cube2 = new Cube({ 1,0,0,1 });
	cube2->translation.x = 2;
	cube2->SetLabel("ColorCUBE");

	sphere = new Sphere_Texture();
	sphere->translation.x = -2;
	sphere->SetLabel("textureSphere");
	
	
	sphere->GetMaterial()->SetDiffuseMap(L"Landscape/Fieldstone_DM.tga");
	sphere->GetMaterial()->SetSpecularMap(L"Landscape/fieldStone_SM.tga");
	sphere->GetMaterial()->SetNormalMap(L"Landscape/fieldStone_NM.tga");

	sphere2 = new Sphere_Color(0.5f, {0.25f,0.45f,0.60f,1});
	sphere2->translation.x = -4;
	sphere2->SetLabel("colorSphere");
}

TextureScene::~TextureScene()
{
	delete cube;
	delete cube2;
	delete sphere;
	delete sphere2;
	
}

void TextureScene::Update()
{
	
	cube->Update();
	cube2->Update();
	sphere->Update();
	sphere2->Update();

	if (KEY_PRESS('W'))
	{
		cube->rotation.x +=  0.0002f;
		cube2->rotation.x += 0.0002f;
		sphere->rotation.y += 0.0002f;
		sphere2->rotation.y += 0.0002f;

	}

}

void TextureScene::PreRender()
{
}

void TextureScene::Render()
{

	cube->Render();
	cube2->Render();

	//RS->ChangeState(D3D11_FILL_WIREFRAME);

	sphere->Render();
	sphere2->Render();
	//RS->ChangeState(D3D11_FILL_SOLID);
	

}

void TextureScene::PostRender()
{
	//cube->Debug();
	//cube2->Debug();
	//sphere->Debug();
	//sphere2->Debug();

	sphere->GetMaterial()->PostRender();

}
