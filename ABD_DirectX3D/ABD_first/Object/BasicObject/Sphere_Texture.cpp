#include "Framework.h"
#include "Sphere_Texture.h"


Sphere_Texture::Sphere_Texture(float radius, UINT sliceCount, UINT stackCount)
	: radius(radius), sliceCount(sliceCount), stackCount(stackCount)
{
	CreateMesh();

	mesh = new Mesh(vertices, indices);

	material = new Material();
	material->SetShader(L"Specular");
	material->SetDiffuseMap(L"Landscape/Bricks.png");

	worldBuffer = new MatrixBuffer();

}

Sphere_Texture::~Sphere_Texture()
{
	delete mesh;
	delete material;
	delete worldBuffer;


}

void Sphere_Texture::Render()
{

	worldBuffer	->SetData(world);
	worldBuffer	->SetVSBuffer(0);

	material	->SetMaterial();
	mesh		->SetMesh();
	
	DC->DrawIndexed(indices.size(), 0, 0);
}

void Sphere_Texture::Update()
{
	Transform::Update();

}


void Sphere_Texture::CreateMesh()
{
	
	for (UINT i = 0; i < stackCount + 1; i++)
	{
		float phi = XM_PI / stackCount * i;

		for (UINT j = 0; j < sliceCount +1; j++)
		{

			float theta = XM_2PI / sliceCount * j;

			VertexType vertex;

			vertex.pos.x = radius * sin(phi) * cos(theta);
			vertex.pos.y = radius * cos(phi);
			vertex.pos.z = radius * sin(phi) * sin(theta);

			vertex.normal = vertex.pos / radius;

			vertex.uv.x = j / (float)sliceCount;
			vertex.uv.y = i / (float)stackCount;

			vertices.push_back(vertex);

		}
	}

	for (UINT j = 0; j < stackCount; j++)
	{
		for (UINT i = 0; i < sliceCount; i++)
		{
			indices.push_back(i + 0 + (sliceCount + 1) * (j + 0));
			indices.push_back(i + 1 + (sliceCount + 1) * (j + 0));
			indices.push_back(i + 0 + (sliceCount + 1) * (j + 1));
							  
			indices.push_back(i + 0 + (sliceCount + 1) * (j + 1));
			indices.push_back(i + 1 + (sliceCount + 1) * (j + 0));
			indices.push_back(i + 1 + (sliceCount + 1) * (j + 1));

		}
	}


	
	

}
