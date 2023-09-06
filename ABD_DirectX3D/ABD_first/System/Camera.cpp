#include "Framework.h"
#include "Camera.h"

Camera::Camera()
{
	viewBuffer = new ViewBuffer();

	transform = new Transform();
	//transform->translation.y = +10;

	//transform->translation = { 120.0f, 100.0f, -20.0f };
	transform->rotation.x = 0.65f;

}

Camera::~Camera()
{
	delete transform;
	delete viewBuffer;
}

void Camera::Update()
{
	FreeMode();
	
}

void Camera::PostRender()
{
	Vector3 pos = transform->translation;
	Vector3 rot = transform->rotation;
	
	ImGui::Text("Camera Pos %.3f, %.3f, %.3f", pos.x, pos.y, pos.z);
	ImGui::Text("Camera Pos %.3f, %.3f, %.3f", rot.x, rot.y, rot.z);

}

void Camera::FreeMode()
{
	if (KEY_PRESS(VK_RBUTTON))
	{
		if (KEY_PRESS(VK_LSHIFT))
		{
			moveSpeed = 50.0f;
		}
		else
		{
			moveSpeed = 20.0f;
		}

		if (KEY_PRESS('A'))
		{
			transform->translation += transform->Left() * moveSpeed * Time::Delta();
		}
		if (KEY_PRESS('D'))
		{
			transform->translation += transform->Right() * moveSpeed * Time::Delta();
		}
		if (KEY_PRESS('S'))
		{
			transform->translation += transform->Backward() * moveSpeed * Time::Delta();
		}
		if (KEY_PRESS('W'))
		{
			transform->translation += transform->Forward() * moveSpeed * Time::Delta();
		}
		if (KEY_PRESS('Q'))
		{
			transform->translation += transform->Up() * moveSpeed * Time::Delta();
		}
		if (KEY_PRESS('E'))
		{
			transform->translation += transform->Down() * moveSpeed * Time::Delta();
		}



		Vector3 direction = MousePos - oldPos;


		transform->rotation.y += direction.x * rotationSpeed * Time::Delta();
		transform->rotation.x += direction.y * rotationSpeed * Time::Delta();
	}

	oldPos = MousePos;

	SetView(); 
}

void Camera::TargetMode()
{
}

void Camera::SetView()
{
	transform->Update();

	// 눈의 위치
	{
		//XMVECTOR eyepos = transform->translation;

		//// 눈이 바라보는 방향
		//XMVECTOR focuspos = transform->translation + transform->Forward();
		//// 카메라의 위 방향 : y축 회전 방향을 정하기 위함
		//XMVECTOR upvector = transform->Up();

		//viewmatrix = XMMatrixLookAtLH(eyepos, focuspos, upvector);
		
		viewmatrix = XMMatrixInverse(nullptr, transform->GetWorld());



		viewBuffer->SetData(viewmatrix, transform->GetWorld());
		viewBuffer->SetVSBuffer(1);
	}
}