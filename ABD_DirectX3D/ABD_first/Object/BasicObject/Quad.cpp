#include "Framework.h"
#include "Quad.h"


Quad::Quad(Vector2 size)
{

	float left	 = -size.x * 0.5f;
	float right  = +size.x * 0.5f;
	float bottom = -size.y * 0.5f;
	float top	 = +size.y * 0.5f;
	
	vertices =
	{
		{Vector3(left,	top, 		0.0f),		Vector2(0,0)},
		{Vector3(right,	top,		0.0f),		Vector2(1,0)},
		{Vector3(left,	bottom,		0.0f),		Vector2(0,1)},
		{Vector3(right, bottom,		0.0f),		Vector2(1,1)},

	};

	indices =
	{
		0, 1, 2,
		2, 1, 3
		

	};

	mesh = new Mesh(vertices, indices);

	material = new Material();
	material->SetShader(L"Texture");
	material->SetDiffuseMap(L"Landscape/box.png");
	
	
	worldBuffer = new MatrixBuffer();


}

Quad::~Quad()
{
	delete mesh;
	delete worldBuffer;

	

}

void Quad::Update()
{
	
	
	Transform::Update();
	
}

void Quad::Render()
{

	//  부모에 있는 월드
	worldBuffer->SetData(world);
	worldBuffer->SetVSBuffer(0);
	

	material->SetMaterial();
	mesh	->SetMesh();


	// draw하기전에만 설정하자
	DC->DrawIndexed(indices.size(), 0, 0);


}
