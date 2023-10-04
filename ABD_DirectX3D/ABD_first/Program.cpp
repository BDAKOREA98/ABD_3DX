#include "Framework.h"
#include "Program.h"


Program::Program()
{
	Initialize();

	//scene = new RobotScene();
	//scene = new TextureScene();
	//scene = new TerrainScene();
	//scene = new TerrainEditorScene();

	scene = new ModelExportScene();

}

Program::~Program()
{
	delete scene;
	Release();
}

void Program::Update()
{
	scene->Update();

	Time::GetInstance()		->Update();
	Keyboard::GetInstance()	->Update();
	Camera::GetInstance()	->Update();

}

void Program::Render()
{

	// Start the Dear ImGui frame
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	if (isWireFrame)
	{
		RS->ChangeState(D3D11_FILL_WIREFRAME);
	}
	else
	{
		RS->ChangeState(D3D11_FILL_SOLID);
	}

	scene->PreRender();




	Device::GetInstance()->Clear();
	Environment::GetInstance()->SetEnvironment();

	scene->Render();
	Time::GetInstance()->Render();

	scene->PostRender();
	Camera::GetInstance()->PostRender();
	Environment::GetInstance()->PostRender();

	ImGui::Checkbox("WireFrame", &isWireFrame);



	ImGui::Render();
	// 실제 Imgui를 그리는 놈이라고 보면 됨 이게 위로 올라가면 큐브 뒤로 그려짐
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	Device::GetInstance()->Present();


}

void Program::Initialize()
{
	//Device		::GetInstance();
	Environment	::GetInstance();
	Keyboard	::GetInstance();
	Time		::GetInstance();
	StateManager::GetInstance();

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGui_ImplWin32_Init(hWnd);
	ImGui_ImplDX11_Init(DEVICE, DC);

}

void Program::Release()
{
	Time		::Delete();
	Device		::Delete();
	Shader		::Delete();
	Keyboard	::Delete();
	Environment	::Delete();
	StateManager::Delete();
	Camera		::Delete();
	Texture		::Delete();
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}
