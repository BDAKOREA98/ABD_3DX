#include "Framework.h"
#include "TerrainScene.h"

TerrainScene::TerrainScene()
{
	terrain = new Terrain(L"LandScape/Bricks.png", L"HeightMap/HeightMap.png");
	robot = new Robot();
	robot->trans->translation.y += 60.0f;

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
	sphere->Update();
	terrain->Update();
	robot->Update();
}

void TerrainScene::PreRender()
{
	
}

void TerrainScene::Render()
{
	terrain->Render();
	sphere->Render();
	robot->Render();
}

void TerrainScene::PostRender()
{
	sphere->PostRender();

	terrain->PostRender();
	

}
