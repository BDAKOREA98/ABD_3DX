#include "Framework.h"
#include "Program.h"


Program::Program()
{
	Initialize();

	//scene = new RobotScene();
	//scene = new TextureScene();
	//scene = new TerrainScene();
	scene = new TerrainEditorScene();


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

	scene->PreRender();




	Device::GetInstance()->Clear();
	Environment::GetInstance()->SetEnvironment();

	scene->Render();
	Time::GetInstance()->Render();
	scene->PostRender();

	Camera::GetInstance()->PostRender();
	Environment::GetInstance()->PostRender();


	ImGui::Render();
	// ���� Imgui�� �׸��� ���̶�� ���� �� �̰� ���� �ö󰡸� ť�� �ڷ� �׷���
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
