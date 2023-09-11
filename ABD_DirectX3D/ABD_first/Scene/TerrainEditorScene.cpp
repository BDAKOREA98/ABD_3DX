#include "Framework.h"
#include "TerrainEditorScene.h"

TerrainEditorScene::TerrainEditorScene()
{
	terrainEditor = new TerrainEditor();
	terrainEditor->GetMaterial()->SetDiffuseMap (L"Landscape/Fieldstone_DM.tga");
	terrainEditor->GetMaterial()->SetSpecularMap(L"Landscape/fieldstone_SM.tga");
	terrainEditor->GetMaterial()->SetNormalMap  (L"Landscape/fieldstone_NM.tga");

	
}

TerrainEditorScene::~TerrainEditorScene()
{
	delete terrainEditor;
}

void TerrainEditorScene::Update()
{
	terrainEditor->Update();

	if (KEY_DOWN(VK_LBUTTON))
	{
		terrainEditor->Picking(&pickerPos);
	}

}

void TerrainEditorScene::PreRender()
{
}

void TerrainEditorScene::Render()
{

	terrainEditor->Render();
}

void TerrainEditorScene::PostRender()
{

	terrainEditor->Debug();
	ImGui::Text("PickerPos : %0.1f, %0.1f, %0.1f" , pickerPos.x, pickerPos.y, pickerPos.z);

}
