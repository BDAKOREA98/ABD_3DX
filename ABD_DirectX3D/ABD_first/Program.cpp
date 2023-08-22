#include "Framework.h"
#include "Program.h"

Program::Program()
{
	Initialize();

	scene = new TutorialScene();

}

Program::~Program()
{
	delete scene;
	Release();
}

void Program::Update()
{
	scene->Update();
}

void Program::Render()
{

	// Start the Dear ImGui frame
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	scene->PreRender();




	Device::GetInstance()->Clear();


	scene->Render();
	scene->PostRender();
	ImGui::Render();
	// 실제 Imgui를 그리는 놈이라고 보면 됨 이게 위로 올라가면 큐브 뒤로 그려짐
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	Device::GetInstance()->Present();


}

void Program::Initialize()
{
	Device::GetInstance();
	Environment::GetInstance();
	// Show the window
	::ShowWindow(hWnd, SW_SHOWDEFAULT);
	::UpdateWindow(hWnd);

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsLight();

	// Setup Platform/Renderer backends
	ImGui_ImplWin32_Init(hWnd);
	ImGui_ImplDX11_Init(DEVICE, DC);

}

void Program::Release()
{
	Device::Dlelte();
	Shader::Delete();
	Environment::Dlelte();

	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}
