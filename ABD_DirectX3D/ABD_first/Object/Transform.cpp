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

}
