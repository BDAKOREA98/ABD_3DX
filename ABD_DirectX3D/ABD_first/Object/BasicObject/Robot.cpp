#include "Framework.h"
#include "Robot.h"

Robot::Robot()
{
	


	trans = new DiffuseCube({ 0,0,0,1 });
	
	Head = new DiffuseCube({ 1,0,0,1 });
	Head->SetParent(trans);
	Head->AddTranslation({ 0,1,0 });

	L_eye = new DiffuseCube({ 1,1,1,1 });
	R_eye = new DiffuseCube({ 1,1,1,1 });
	mouse = new DiffuseCube({ 1,1,1,1 });

	L_eye->SetParent(Head);
	R_eye->SetParent(Head);
	mouse->SetParent(Head);

	L_eye->AddScale({ -0.8f, -0.8f, -0.8f });
	R_eye->AddScale({ -0.8f, -0.8f, -0.8f });
	mouse->AddScale({ -0.2f, -0.8f, -0.8f });

	L_eye->AddTranslation({ -0.7f , 0.0f , - 1.0f});
	R_eye->AddTranslation({+0.7f , 0.0f  , - 1.0f});
	mouse->AddTranslation({ 0.0f , -0.6f , - 1.0f });

	body = new DiffuseCube({ 1,1,1,1 });
	body->AddScale({ 1.5f, 1.5f,1.5f });
	body->SetParent(trans);
	body->AddTranslation({0.0f, -3.0f, 0.0f});

			
	L_Arm1	= new DiffuseCube({ 0,1,0,1 });
	L_Arm2	= new DiffuseCube({ 0,1,0,1 });
	L_Arm3	= new DiffuseCube({ 0,1,0,1 });
	L_Arm1->SetParent(trans);
	L_Arm2->SetParent(L_Arm1);
	L_Arm3->SetParent(L_Arm2);

	L_Arm1->AddScale({ -0.4f, -0.4f, -0.4f });
	
	L_Arm1->AddTranslation({ -4.0f,-2.0f,0.0f });
	L_Arm2->AddTranslation({ 0.0f,-3.0f,0.0f });
	L_Arm3->AddTranslation({ 0.0f,-3.0f,0.0f });
	


	R_Arm1	= new DiffuseCube({ 0,0,1,1 });
	R_Arm2	= new DiffuseCube({ 0,0,1,1 });
	R_Arm3	= new DiffuseCube({ 0,0,1,1 });

	R_Arm1->SetParent(trans);
	R_Arm2->SetParent(R_Arm1);
	R_Arm3->SetParent(R_Arm2);
	R_Arm1->AddScale({ -0.4f, -0.4f, -0.4f });

	
	R_Arm1->AddTranslation({ +4.0f,-2.0f,0.0f });
	R_Arm2->AddTranslation({ +0.0f,-3.0f,0.0f });
	R_Arm3->AddTranslation({ +0.0f,-3.0f,0.0f });

			
	L_Leg1	= new DiffuseCube({ 1,0,0.5f,1 });
	L_Leg2	= new DiffuseCube({ 1,0,0.5f,1 });
	L_Leg3	= new DiffuseCube({ 1,0,0.5f,1 });
	L_Leg4	= new DiffuseCube({ 1,0,0.5f,1 });
	
	L_Leg1->SetParent(trans)	 ;
	L_Leg2->SetParent(L_Leg1);
	L_Leg3->SetParent(L_Leg2);
	L_Leg4->SetParent(L_Leg3);


	L_Leg1->AddScale({ -0.3f, -0.3f, -0.3f });

	L_Leg1->AddTranslation({-2.0f, -6.0f, 0.0f})		 ;
	L_Leg2->AddTranslation({+0.0f, -3.0f, 0.0f})	 ;
	L_Leg3->AddTranslation({+0.0f, -3.0f, 0.0f})	 ;
	L_Leg4->AddTranslation({+0.0f, -3.0f, 0.0f });

	R_Leg1	= new DiffuseCube({ 1,1,0,1 });
	R_Leg2	= new DiffuseCube({ 1,1,0,1 });
	R_Leg3	= new DiffuseCube({ 1,1,0,1 });
	R_Leg4	= new DiffuseCube({ 1,1,0,1 });


	R_Leg1->SetParent(trans);
	R_Leg2->SetParent(R_Leg1);
	R_Leg3->SetParent(R_Leg2);
	R_Leg4->SetParent(R_Leg3);


	R_Leg1->AddScale({ -0.3f, -0.3f, -0.3f });

	R_Leg1->AddTranslation({ +2.0f, -6.0f, 0.0f });
	R_Leg2->AddTranslation({ +0.0f, -3.0f, 0.0f });
	R_Leg3->AddTranslation({ +0.0f, -3.0f, 0.0f });
	R_Leg4->AddTranslation({ +0.0f, -3.0f, 0.0f });


	

}

Robot::~Robot()
{
		delete Head	 ;
		delete body	 ;
		delete trans ;
		delete L_Arm1;
		delete L_Arm2;
		delete L_Arm3;
		delete R_Arm1;
		delete R_Arm2;
		delete R_Arm3;
		delete L_Leg1;
		delete L_Leg2;
		delete L_Leg3;
		delete L_Leg4;
		delete R_Leg1;
		delete R_Leg2;
		delete R_Leg3;
		delete R_Leg4;
		delete L_eye;
		delete R_eye;
		delete mouse;
}

void Robot::Update()
{
	InputKey();
	Transform::Update();
		Head  ->Update();
		body  ->Update();
		trans ->Update();
		L_Arm1->Update();
		L_Arm2->Update();
		L_Arm3->Update();
		R_Arm1->Update();
		R_Arm2->Update();
		R_Arm3->Update();
		L_Leg1->Update();
		L_Leg2->Update();
		L_Leg3->Update();
		L_Leg4->Update();
		R_Leg1->Update();
		R_Leg2->Update();
		R_Leg3->Update();
		R_Leg4->Update();
		L_eye->Update();
		R_eye->Update();
		mouse->Update();
}

void Robot::Render()
{
	//	trans ->Render();
		Head  ->Render();
		body  ->Render();
		L_Arm1->Render();
		L_Arm2->Render();
		L_Arm3->Render();
		R_Arm1->Render();
		R_Arm2->Render();
		R_Arm3->Render();
		L_Leg1->Render();
		L_Leg2->Render();
		L_Leg3->Render();
		L_Leg4->Render();
		R_Leg1->Render();
		R_Leg2->Render();
		R_Leg3->Render();
		R_Leg4->Render();
		L_eye->Render();
		R_eye->Render();
		mouse->Render();


}

void Robot::InputKey()
{

	if ( KEY_PRESS('S') && active == false)
	{
		
		trans->translation += trans->Forward() * Time::Delta();

		L_Arm1->AddRotation({ 0.001f, 0.0f, 0.0f });
		L_Arm2->AddRotation({ 0.001f, 0.0f, 0.0f });
		L_Arm3->AddRotation({ 0.001f, 0.0f, 0.0f });

		R_Arm1->AddRotation({ -0.001f, 0.0f, 0.0f });
		R_Arm2->AddRotation({ -0.001f, 0.0f, 0.0f });
		R_Arm3->AddRotation({ -0.001f, 0.0f, 0.0f });

		
		R_Leg1->AddRotation({ 0.001f, 0.0f, 0.0f });
		R_Leg2->AddRotation({ 0.001f, 0.0f, 0.0f });
		R_Leg3->AddRotation({ 0.001f, 0.0f, 0.0f });
		R_Leg4->AddRotation({ 0.001f, 0.0f, 0.0f });

		L_Leg1->AddRotation({ -0.001f, 0.0f, 0.0f });
		L_Leg2->AddRotation({ -0.001f, 0.0f, 0.0f });
		L_Leg3->AddRotation({ -0.001f, 0.0f, 0.0f });
		L_Leg4->AddRotation({ -0.001f, 0.0f, 0.0f });

		if (L_Arm1->rotation.x >= 0.5*PI)
		{
			active = true;
		}

	}
	if (KEY_PRESS('S') && active)
	{
		trans->translation += trans->Forward() * Time::Delta();
		
		L_Arm1->AddRotation({ -0.001f, 0.0f, 0.0f });
		L_Arm2->AddRotation({ -0.001f, 0.0f, 0.0f });
		L_Arm3->AddRotation({ -0.001f, 0.0f, 0.0f });

		R_Arm1->AddRotation({ +0.001f, 0.0f, 0.0f });
		R_Arm2->AddRotation({ +0.001f, 0.0f, 0.0f });
		R_Arm3->AddRotation({ +0.001f, 0.0f, 0.0f });


		R_Leg1->AddRotation({ -0.001f, 0.0f, 0.0f });
		R_Leg2->AddRotation({ -0.001f, 0.0f, 0.0f });
		R_Leg3->AddRotation({ -0.001f, 0.0f, 0.0f });
		R_Leg4->AddRotation({ -0.001f, 0.0f, 0.0f });

		L_Leg1->AddRotation({ +0.001f, 0.0f, 0.0f });
		L_Leg2->AddRotation({ +0.001f, 0.0f, 0.0f });
		L_Leg3->AddRotation({ +0.001f, 0.0f, 0.0f });
		L_Leg4->AddRotation({ +0.001f, 0.0f, 0.0f });

		if (L_Arm1->rotation.x <= -0.5 * PI)
		{
			active = false;
		}

	}

	if (KEY_PRESS('D') && active == false)
	{

		trans->translation += trans->Right() * Time::Delta();

		L_Arm1->AddRotation({ 0.001f, 0.0f, 0.0f });
		L_Arm2->AddRotation({ 0.001f, 0.0f, 0.0f });
		L_Arm3->AddRotation({ 0.001f, 0.0f, 0.0f });

		R_Arm1->AddRotation({ -0.001f, 0.0f, 0.0f });
		R_Arm2->AddRotation({ -0.001f, 0.0f, 0.0f });
		R_Arm3->AddRotation({ -0.001f, 0.0f, 0.0f });


		R_Leg1->AddRotation({ 0.001f, 0.0f, 0.0f });
		R_Leg2->AddRotation({ 0.001f, 0.0f, 0.0f });
		R_Leg3->AddRotation({ 0.001f, 0.0f, 0.0f });
		R_Leg4->AddRotation({ 0.001f, 0.0f, 0.0f });

		L_Leg1->AddRotation({ -0.001f, 0.0f, 0.0f });
		L_Leg2->AddRotation({ -0.001f, 0.0f, 0.0f });
		L_Leg3->AddRotation({ -0.001f, 0.0f, 0.0f });
		L_Leg4->AddRotation({ -0.001f, 0.0f, 0.0f });

		if (L_Arm1->rotation.x >= 0.5 * PI)
		{
			active = true;
		}

	}
	if (KEY_PRESS('D') && active)
	{
		trans->translation += trans->Right() * Time::Delta();

		L_Arm1->AddRotation({ -0.001f, 0.0f, 0.0f });
		L_Arm2->AddRotation({ -0.001f, 0.0f, 0.0f });
		L_Arm3->AddRotation({ -0.001f, 0.0f, 0.0f });

		R_Arm1->AddRotation({ +0.001f, 0.0f, 0.0f });
		R_Arm2->AddRotation({ +0.001f, 0.0f, 0.0f });
		R_Arm3->AddRotation({ +0.001f, 0.0f, 0.0f });


		R_Leg1->AddRotation({ -0.001f, 0.0f, 0.0f });
		R_Leg2->AddRotation({ -0.001f, 0.0f, 0.0f });
		R_Leg3->AddRotation({ -0.001f, 0.0f, 0.0f });
		R_Leg4->AddRotation({ -0.001f, 0.0f, 0.0f });

		L_Leg1->AddRotation({ +0.001f, 0.0f, 0.0f });
		L_Leg2->AddRotation({ +0.001f, 0.0f, 0.0f });
		L_Leg3->AddRotation({ +0.001f, 0.0f, 0.0f });
		L_Leg4->AddRotation({ +0.001f, 0.0f, 0.0f });

		if (L_Arm1->rotation.x <= -0.5 * PI)
		{
			active = false;
		}

	}

	if (KEY_PRESS('A') && active == false)
	{

		trans->translation += trans->Left() * Time::Delta();

		L_Arm1->AddRotation({ 0.001f, 0.0f, 0.0f });
		L_Arm2->AddRotation({ 0.001f, 0.0f, 0.0f });
		L_Arm3->AddRotation({ 0.001f, 0.0f, 0.0f });

		R_Arm1->AddRotation({ -0.001f, 0.0f, 0.0f });
		R_Arm2->AddRotation({ -0.001f, 0.0f, 0.0f });
		R_Arm3->AddRotation({ -0.001f, 0.0f, 0.0f });


		R_Leg1->AddRotation({ 0.001f, 0.0f, 0.0f });
		R_Leg2->AddRotation({ 0.001f, 0.0f, 0.0f });
		R_Leg3->AddRotation({ 0.001f, 0.0f, 0.0f });
		R_Leg4->AddRotation({ 0.001f, 0.0f, 0.0f });

		L_Leg1->AddRotation({ -0.001f, 0.0f, 0.0f });
		L_Leg2->AddRotation({ -0.001f, 0.0f, 0.0f });
		L_Leg3->AddRotation({ -0.001f, 0.0f, 0.0f });
		L_Leg4->AddRotation({ -0.001f, 0.0f, 0.0f });

		if (L_Arm1->rotation.x >= 0.5 * PI)
		{
			active = true;
		}

	}
	if (KEY_PRESS('A') && active)
	{
		trans->translation += trans->Left() * Time::Delta();

		L_Arm1->AddRotation({ -0.001f, 0.0f, 0.0f });
		L_Arm2->AddRotation({ -0.001f, 0.0f, 0.0f });
		L_Arm3->AddRotation({ -0.001f, 0.0f, 0.0f });

		R_Arm1->AddRotation({ +0.001f, 0.0f, 0.0f });
		R_Arm2->AddRotation({ +0.001f, 0.0f, 0.0f });
		R_Arm3->AddRotation({ +0.001f, 0.0f, 0.0f });


		R_Leg1->AddRotation({ -0.001f, 0.0f, 0.0f });
		R_Leg2->AddRotation({ -0.001f, 0.0f, 0.0f });
		R_Leg3->AddRotation({ -0.001f, 0.0f, 0.0f });
		R_Leg4->AddRotation({ -0.001f, 0.0f, 0.0f });

		L_Leg1->AddRotation({ +0.001f, 0.0f, 0.0f });
		L_Leg2->AddRotation({ +0.001f, 0.0f, 0.0f });
		L_Leg3->AddRotation({ +0.001f, 0.0f, 0.0f });
		L_Leg4->AddRotation({ +0.001f, 0.0f, 0.0f });

		if (L_Arm1->rotation.x <= -0.5 * PI)
		{
			active = false;
		}

	}

	if (KEY_PRESS('W') && active == false)
	{

		trans->translation += trans->Backward() * Time::Delta();

		L_Arm1->AddRotation({ 0.001f, 0.0f, 0.0f });
		L_Arm2->AddRotation({ 0.001f, 0.0f, 0.0f });
		L_Arm3->AddRotation({ 0.001f, 0.0f, 0.0f });

		R_Arm1->AddRotation({ -0.001f, 0.0f, 0.0f });
		R_Arm2->AddRotation({ -0.001f, 0.0f, 0.0f });
		R_Arm3->AddRotation({ -0.001f, 0.0f, 0.0f });


		R_Leg1->AddRotation({ 0.001f, 0.0f, 0.0f });
		R_Leg2->AddRotation({ 0.001f, 0.0f, 0.0f });
		R_Leg3->AddRotation({ 0.001f, 0.0f, 0.0f });
		R_Leg4->AddRotation({ 0.001f, 0.0f, 0.0f });

		L_Leg1->AddRotation({ -0.001f, 0.0f, 0.0f });
		L_Leg2->AddRotation({ -0.001f, 0.0f, 0.0f });
		L_Leg3->AddRotation({ -0.001f, 0.0f, 0.0f });
		L_Leg4->AddRotation({ -0.001f, 0.0f, 0.0f });

		if (L_Arm1->rotation.x >= 0.5 * PI)
		{
			active = true;
		}

	}
	if (KEY_PRESS('W') && active)
	{
		trans->translation += trans->Backward() * Time::Delta();

		L_Arm1->AddRotation({ -0.001f, 0.0f, 0.0f });
		L_Arm2->AddRotation({ -0.001f, 0.0f, 0.0f });
		L_Arm3->AddRotation({ -0.001f, 0.0f, 0.0f });

		R_Arm1->AddRotation({ +0.001f, 0.0f, 0.0f });
		R_Arm2->AddRotation({ +0.001f, 0.0f, 0.0f });
		R_Arm3->AddRotation({ +0.001f, 0.0f, 0.0f });


		R_Leg1->AddRotation({ -0.001f, 0.0f, 0.0f });
		R_Leg2->AddRotation({ -0.001f, 0.0f, 0.0f });
		R_Leg3->AddRotation({ -0.001f, 0.0f, 0.0f });
		R_Leg4->AddRotation({ -0.001f, 0.0f, 0.0f });

		L_Leg1->AddRotation({ +0.001f, 0.0f, 0.0f });
		L_Leg2->AddRotation({ +0.001f, 0.0f, 0.0f });
		L_Leg3->AddRotation({ +0.001f, 0.0f, 0.0f });
		L_Leg4->AddRotation({ +0.001f, 0.0f, 0.0f });

		if (L_Arm1->rotation.x <= -0.5 * PI)
		{
			active = false;
		}

	}

	if (KEY_PRESS('E'))
	{
		trans->rotation.y += 0.001f;
	}
	if (KEY_PRESS('Q'))
	{
		trans->rotation.y -= 0.001f;
	}


}

void Robot::PostRender()
{
	L_Arm1->PostRender();

}
