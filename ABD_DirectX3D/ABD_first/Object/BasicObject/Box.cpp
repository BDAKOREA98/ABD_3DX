#include "Framework.h"
#include "Box.h"



Box::Box(Vector2 size)
{
	float left = -size.x * 0.5f;
	float right = +size.x * 0.5f;
	float bottom = -size.y * 0.5f;
	float top = +size.y * 0.5f;

	vertices =
	{		// ����
		{Vector3(left,	top, 		0.0f),		Vector2(0,0)},
		{Vector3(right,	top,		0.0f),		Vector2(1,0)},
		{Vector3(left,	bottom,		0.0f),		Vector2(0,1)},
		{Vector3(right, bottom,		0.0f),		Vector2(1,1)},
		 //  ����
		{Vector3(left,	top, 		1.0f),		Vector2(0,0)},//  1  1
		{Vector3(left,	top,		0.0f),		Vector2(1,0)},//  2
		{Vector3(left,	bottom,		1.0f),		Vector2(0,1)},//    2  
		{Vector3(left,  bottom,		0.0f),		Vector2(1,1)},// 3  3
		// ������
		{Vector3(right,	top, 		0.0f),		Vector2(0,0)},//8   1	1
		{Vector3(right,	top,		1.0f),		Vector2(1,0)},//9   2	
		{Vector3(right,	bottom,		1.0f),		Vector2(0,1)},//10		2
		{Vector3(right, bottom,		0.0f),		Vector2(1,1)},//11  3	3
		// ����
		{Vector3(left,	top, 		1.0f),		Vector2(0,0)},// 12 1 1
		{Vector3(right,	top,		1.0f),		Vector2(1,0)},// 13 2 
		{Vector3(left,	top,		0.0f),		Vector2(0,1)},// 14 3 2
		{Vector3(right, top,		0.0f),		Vector2(1,1)},// 15   3
		// �Ʒ���
		{Vector3(left,	bottom,		0.0f),		Vector2(0,0)},// 16 1	1
		{Vector3(right, bottom,		0.0f),		Vector2(1,0)},// 17 2
		{Vector3(left,	bottom,		1.0f),		Vector2(0,1)},// 18 3	2
		{Vector3(right,	bottom,		1.0f),		Vector2(1,1)},// 19		3
		// ����
		{Vector3(right,	top,		1.0f),		Vector2(0,0)},// 20 1 1
		{Vector3(left,	top, 		1.0f),		Vector2(1,0)},// 21 2
		{Vector3(right, bottom,		1.0f),		Vector2(0,1)},// 22	  2
		{Vector3(left,	bottom,		1.0f),		Vector2(1,1)},// 23 3 3


	};

	indices =
	{	// ����
		0, 1, 2,
		2, 1, 3,
		// ���� 
		4, 5, 6,
		5, 4, 7,
		// ����
		8, 9, 10,
		9, 8, 11,
		// ����
		12, 13, 14,
		13, 12, 15,
		// �޸�
		16,17,18,
		17,16,19,
		//�Ʒ���
		20,21,22,
		21,20,23

	};

	mesh = new Mesh(vertices, indices);

	material = new Material();
	material->SetShader(L"Texture");
	material->SetDiffuseMap(L"Landscape/box.png");

	worldBuffer = new MatrixBuffer();


	
}

Box::~Box()
{
	delete mesh;
	delete worldBuffer;

	
}

void Box::Update()
{
	Transform::Update();
	if (Key_PRESS(VK_LBUTTON))
	{
		AddRotation(Vector3(0.01f, 0.00f, 0));
	}
}

void Box::Render()
{
	//  �θ� �ִ� ����
	worldBuffer->SetData(world);
	worldBuffer->SetVSBuffer(0);


	material->SetMaterial();
	mesh->SetMesh();


	




	// draw�ϱ������� ��������
	DC->DrawIndexed(indices.size(), 0, 0);
}

void Box::PosRender()
{
	
}
