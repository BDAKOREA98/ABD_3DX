#include "Framework.h"
#include "TerrainScene.h"

TerrainScene::TerrainScene()
{
	terrain = new Terrain(L"LandScape/dirt.png", L"HeightMap/HeightMap.png");
	robot = new Robot();
	robot->trans->translation.y += 10.0f;
}

TerrainScene::~TerrainScene()
{
	delete terrain;
	delete robot;
}

void TerrainScene::Update()
{
	terrain->Update();
	robot->Update();
}

void TerrainScene::PreRender()
{

}

void TerrainScene::Render()
{
	terrain->Render();
	robot->Render();
}

void TerrainScene::PostRender()
{

}
