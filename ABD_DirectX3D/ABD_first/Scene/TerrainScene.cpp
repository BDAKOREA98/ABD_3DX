#include "Framework.h"
#include "TerrainScene.h"

TerrainScene::TerrainScene()
{
	terrain = new Terrain(L"LandScape/Bricks.png", L"HeightMap/HeightMap.png");
	robot = new Robot();
	robot->trans->translation.y += 30.0f;





	CAMERA->translation = { 0, 100, -100 };
	//sphere = new Sphere_Color(10.0f, { 1.0f, 0.0f, 0.0f, 1.0f });
	

}

TerrainScene::~TerrainScene()
{
	delete terrain;
	delete robot;
	//delete sphere;
}

void TerrainScene::Update()
{
	//sphere->Update();
	terrain->Update();
	robot->Update();
}

void TerrainScene::PreRender()
{
	
}

void TerrainScene::Render()
{
	robot->Render();
	terrain->Render();
	//sphere->Render();
}

void TerrainScene::PostRender()
{
	//sphere->Debug();

	terrain->PostRender();
	

}
