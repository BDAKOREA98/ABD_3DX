#include "Framework.h"
#include "TerrainScene.h"

TerrainScene::TerrainScene()
{
	terrain = new Terrain(L"LandScape/dirt.png", L"HeightMap/HeightMap.png");
	robot = new Robot();
	robot->trans->translation.y += 10.0f;

	sphere = new Sphere(10.0f, { 0.1f, 0.4f, 0.5f, 1.0f });
	

}

TerrainScene::~TerrainScene()
{
	delete terrain;
	delete robot;
	delete sphere;
}

void TerrainScene::Update()
{
	terrain->Update();
	robot->Update();
	sphere->Update();
}

void TerrainScene::PreRender()
{
	
}

void TerrainScene::Render()
{
	terrain->Render();
	robot->Render();
	sphere->Render();
}

void TerrainScene::PostRender()
{
	sphere->PostRender();

}
