#include "Framework.h"
#include "Transform.h"

Transform::Transform()
{
	world = XMMatrixIdentity();

}

Transform::~Transform()
{
}

void Transform::Update()
{
	UpdateWorld();

}

void Transform::UpdateWorld()
{
	world = XMMatrixTransformation
	(
		pivot,
		XMQuaternionIdentity(),
		scale,
		pivot,
		XMQuaternionRotationRollPitchYaw(rotation.x, rotation.y, rotation.z),
		translation
	);

	
	// parent가 private인데 직접접근이 가능한 이유 : 동일클래스이기 때문임
	if (parent != nullptr)
	{
		world *= parent->world;
	}

	XMFLOAT4X4 fworld;

	XMStoreFloat4x4(&fworld, world);

	right	= Vector3(fworld._11, fworld._12, fworld._13).GetNormalize();
	up		= Vector3(fworld._21, fworld._22, fworld._23).GetNormalize();
	forward = Vector3(fworld._31, fworld._32, fworld._33).GetNormalize();
	
	
	XMVECTOR outS, outR, outT;

	XMMatrixDecompose(&outS, &outR, &outT, world);

	globalScale		= outS;
	globalRotation	= outR;
	globalPosition	= outT;




}

void Transform::Debug()
{
	
	if (ImGui::BeginMenu(label.c_str()))
	{
		ImGui::DragFloat3("Scale", (float*)&scale, 0.01f, 0.01f, 100.0f);
		//ImGui::DragFloat3("rotation",   (float*)&rotation,      0.01f,  -XM_2PI,    XM_2PI);
		ImGui::SliderAngle("rotation.x", &rotation.x);
		ImGui::SliderAngle("rotation.y", &rotation.y);
		ImGui::SliderAngle("rotation.z", &rotation.z);
		ImGui::DragFloat3("translation", (float*)&translation, 0.01f, -WIN_WIDTH, WIN_WIDTH);

		ImGui::EndMenu();
	}
}
