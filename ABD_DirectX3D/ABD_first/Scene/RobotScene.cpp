#include "Framework.h"
#include "RobotScene.h"

RobotScene::RobotScene()
{
	body = new Cube(PURPLE);
	body->AddScale(Vector3(0.5f, 0.5f, 0.5f));
	bodytrans = new Cube(PURPLE);
	bodytrans->SetParent(body);
	bodytrans2 = new Cube(PURPLE);
	bodytrans2->SetParent(body);
	
	head = new Cube(BLUE);
	head->SetParent(body);
	head->AddScale(Vector3(-0.5f, -0.5f, -0.5f));
	head->AddTranslation(Vector3(000, 1.5f, 000));

	

	arm_L = new Cube(GREEN);
	arm_L->SetParent(bodytrans2);
	arm_L->AddScale(Vector3(-0.8f, 0.5f, -0.5f));
	arm_L->AddTranslation(Vector3(-1.0f, -1.0f, 0.0f));

	arm_R = new Cube(GREEN);
	arm_R->SetParent(bodytrans);
	arm_R->AddScale(Vector3(-0.8f, 0.5f, -0.5f));
	arm_R->AddTranslation(Vector3(+1.0f, -1.0f, 0.0f));


	leg_L = new Cube(RED);
	leg_L->SetParent(bodytrans2);
	leg_L->AddScale(Vector3(-1.3f, 1.0f, -0.5f));
	leg_L->AddTranslation(Vector3(-0.5f, -2.0f, 0.0f));
	

	leg_R = new Cube(RED);
	leg_R->SetParent(bodytrans);
	leg_R->AddScale(Vector3(-1.3f, 1.0f, -0.5f));
	leg_R->AddTranslation(Vector3(+0.5f, -2.0f, 0.0f));

	

}

RobotScene::~RobotScene()
{
	delete  head;
	delete  body;
	delete  arm_L;
	delete  arm_R;
	delete  leg_L;
	delete  leg_R;
}

void RobotScene::Update()
{
	inputKey();
	bodytrans->Update();
	bodytrans2->Update();
	head ->Update();
	body ->Update();
	arm_L->Update();
	arm_R->Update();
	leg_L->Update();
	leg_R->Update();

}

void RobotScene::PreRender()
{



}

void RobotScene::Render()
{
		head->Render();
		body ->Render();
		arm_L->Render();
		arm_R->Render();
		leg_L->Render();
		leg_R->Render();
}

void RobotScene::PostRender()
{
	
	bodytrans->Debug();

}

void RobotScene::inputKey()
{
	if (KEY_PRESS('W'))
	{
		body->translation += body->Backward() * Time::Delta();

		if (active)
		{
			key += 0.003f;
			bodytrans->AddRotation(Vector3(+0.003f, 0.0f, 0.0f));
			arm_R->rotation.x * 0.5f;

		}
		if (key >= PI * 90 / 180)
		{
			active = false;
			active2 = true;
			active_L = true;

			bodytrans->AddRotation(Vector3(-0.003f, 0.0f, 0.0f));
		
		}
		if (active2 == true && bodytrans->rotation.x < 0.0)
		{
			key = 0;
			active = true;
			active2 = false;
			
		}
		if (active_L)
		{
			key2 += 0.003f;
			bodytrans2->AddRotation(Vector3(+0.003f, 0.0f, 0.0f));
			arm_L->rotation.x * 0.5f;

		}
		if (key2 >= PI * 90 / 180)
		{
			active_L = false;
			active2_L = true;

			bodytrans2->AddRotation(Vector3(-0.003f, 0.0f, 0.0f));

		}
		if (active2_L == true && bodytrans2->rotation.x < 0.0)
		{
			key2 = 0;
			active_L = true;
			active2_L = false;

		}
	


	

	}

	if (KEY_PRESS(VK_LEFT))
	{
		body->AddRotation(Vector3(0.0f, 0.002f, 0.0f));
	}


}
