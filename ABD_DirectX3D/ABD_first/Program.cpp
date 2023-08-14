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
	scene->PostRender();
	scene->Render();
	scene->PreRender();
}

void Program::Initialize()
{
}

void Program::Release()
{
}
