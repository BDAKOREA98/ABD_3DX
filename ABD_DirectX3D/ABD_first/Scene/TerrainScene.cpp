#include "Framework.h"
#include "TerrainScene.h"

TerrainScene::TerrainScene()
{
	terrain = new Terrain(L"LandScape/Bricks.png", L"HeightMap/HeightMap.png");
	robot = new Robot();
	robot->trans->translation.y += 60.0f;
	robot->trans->AddScale({ -1.5f, -1.5f, -1.5f });
	terrain->SetLabel("Terrain");

	robot->trans->SetLabel("Robot");

	CAMERA->translation = { 0, 100, -100 };
	sphere = new Sphere_Color(10.0f, { 1.0f, 0.0f, 0.0f, 1.0f });
	sphere->SetLabel("Sphere");

	RawData();
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
	//RS->ChangeState(D3D11_FILL_WIREFRAME);
	terrain->Render();
	//RS->ChangeState(D3D11_FILL_SOLID);
	sphere->Render();
	robot->Render();
}

void TerrainScene::PostRender()
{
	sphere->PostRender();
//
	terrain->PostRender();
	robot->PostRender();
	ImGui::Text("PickerPos : %0.4f, %0.4f, %0.4f", pickerPos.x, pickerPos.y, pickerPos.z);
	

}

void TerrainScene::RawData()
{
	/*ComputeShader* shader = Shader::GetCS(L"ByteAddress");

	struct Output
	{
		UINT groupID[3];
		UINT groupThreadID[3];
		UINT dispatchThreadID[3];
		UINT groupIndex;
	};

	UINT size = 10 * 8 * 3;

	Output* output = new Output[size];

	RawBuffer* buffer = new RawBuffer(nullptr, sizeof(Output) * size);

	ID3D11UnorderedAccessView* uav = buffer->GetUAV();

	shader->SetShader();
	DC->CSSetUnorderedAccessViews(0, 1, &uav, nullptr);
	DC->Dispatch(1, 1, 1);

	buffer->Copy(output, sizeof(Output) * size);

	FILE* file;
	fopen_s(&file, "_TextData/RawTest.csv", "w");

	for (UINT i = 0; i < size; i++)
	{
		fprintf
		(
			file,
			"%d, %d, %d, %d, %d, %d,%d, %d, %d,%d, %d\n",
			i,
			output[i].groupID[0],
			output[i].groupID[1],
			output[i].groupID[2],

			output[i].groupThreadID[0],
		output[i].groupThreadID[1],
		output[i].groupThreadID[2],

		output[i].dispatchThreadID[0],
		output[i].dispatchThreadID[1],
		output[i].dispatchThreadID[2],

		output[i].groupIndex
		);

	}

	fclose(file);

	delete buffer;
	delete output;*/


}
