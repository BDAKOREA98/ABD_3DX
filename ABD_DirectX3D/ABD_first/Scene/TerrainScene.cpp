#include "Framework.h"
#include "TerrainScene.h"

TerrainScene::TerrainScene()
{
	terrain = new Terrain(L"LandScape/Bricks.png", L"HeightMap/HeightMap.png");
	robot = new Robot();
	robot->trans->translation.y += 60.0f;
	robot->trans->AddScale({ -1.5f, -1.5f, -1.5f });
	terrain->SetLabel("Terrain");



	CAMERA->translation = { 0, 100, -100 };
	sphere = new Sphere_Color(10.0f, { 1.0f, 0.0f, 0.0f, 1.0f });
	sphere->SetLabel("Sphere");

}

TerrainScene::~TerrainScene()
{
	delete terrain;
	delete robot;
	delete sphere;
}

void TerrainScene::Update()
{
	if (KEY_DOWN(VK_LBUTTON))
	{
		terrain->Picking(&pickerPos);
		robot->trans->SetPosition({ pickerPos.x,pickerPos.y +20  , pickerPos.z });
	}

	sphere->Update();
	terrain->Update();
	robot->Update();
}

void TerrainScene::PreRender()
{
	
}

void TerrainScene::Render()
{
	RS->ChangeState(D3D11_FILL_WIREFRAME);
	terrain->Render();
	RS->ChangeState(D3D11_FILL_SOLID);
	sphere->Render();
	robot->Render();
}

void TerrainScene::PostRender()
{
//	sphere->PostRender();
//
//	terrain->PostRender();
	ImGui::Text("PickerPos : %0.4f, %0.4f, %0.4f", pickerPos.x, pickerPos.y, pickerPos.z);
	

}
