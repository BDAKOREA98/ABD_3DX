#include "Framework.h"
#include "Terrain.h"



Terrain::Terrain(wstring diffuseFile, wstring heightFile)
{
	material = new Material();
	material->SetShader(L"NormalMapping");
	material->SetSpecularMap(L"Landscape/fieldStone_SM.tga");
	material->SetNormalMap(L"Landscape/fieldstone_NM.tga");
	material->SetDiffuseMap(diffuseFile);


	worldBuffer = new MatrixBuffer();


	heightMap = Texture::Get(heightFile);

	CreateMesh();

	CreateNormal();

	mesh = new Mesh(vertices, indices);

}

Terrain::~Terrain()
{
	delete worldBuffer;
	delete mesh;
	delete material;
}

void Terrain::Render()
{
	worldBuffer->SetData(world);
	worldBuffer->SetVSBuffer(0);
	mesh->SetMesh();
	material->SetMaterial();

	DC->DrawIndexed(indices.size(), 0, 0);
}

void Terrain::Update()
{
	Transform::Update();
}

void Terrain::PostRender()
{
	material->PostRender();
	Debug();
}

bool Terrain::Picking(OUT Vector3* position)
{
	Ray ray = Camera::GetInstance()->ScreenPointToRay(MousePos);

	for (UINT z = 0; z < height - 1; z++)
	{
		for (UINT x = 0; x < width - 1; x++)
		{
			UINT index[4];

			index[0] = (x + 0) + width * (z + 0);
			index[1] = (x + 1) + width * (z + 0);
			index[2] = (x + 0) + width * (z + 1);
			index[3] = (x + 1) + width * (z + 1);

			Vector3 Pos[4];
			for (UINT i = 0; i < 4; i++)
			{
				Pos[i] = vertices[index[i]].pos;

			}

			float distance = 0.0f;
			// Intersects는 DX에서 RayCasting을 위해 만든 함수이나 알고리즘이 별로임

			if (TriangleTests::Intersects(ray.origin, ray.direction, Pos[0], Pos[1], Pos[2], distance))
			{
				*position = ray.origin + ray.direction * distance;

				return true;
			}
			if (TriangleTests::Intersects(ray.origin, ray.direction, Pos[2], Pos[1], Pos[3], distance))
			{
				*position = ray.origin + ray.direction * distance;

				return true;
			}
		}
	}



	return false;
}

void Terrain::CreateMesh()
{
	width = heightMap->GetSize().x;
	height = heightMap->GetSize().y;

	vector<Vector4> colors = heightMap->ReadPixel();



	//  vertex
	for (float z = 0; z < height; z++)
	{
		for (float x = 0; x < width; x++)
		{
			VertexTextureNormal vertex;
			vertex.pos = Vector3(x, 0, z);


			vertex.uv.x = x / (width - 1);
			vertex.uv.y = 1 - z / (height - 1);

			/////////////HeightMap
			UINT index = x + z * width;

			vertex.pos.y = colors[index].x * MAP_HEIGHT;


			vertices.push_back(vertex);

		}
	}

	//indices
	for (float z = 0; z < height - 1; z++)
	{
		for (float x = 0; x < width - 1; x++)
		{

			indices.push_back(x + 0 + (width) * (z + 1)); // 왼쪽위		//
			indices.push_back(x + 1 + (width) * (z + 1)); // 오른쪽위	//
			indices.push_back(x + 0 + (width) * (z + 0)); // 왼쪽아래    //


			indices.push_back(x + 0 + (width) * (z + 0)); // 왼쪽아래     //
			indices.push_back(x + 1 + (width) * (z + 1)); // 오른쪽위	//
			indices.push_back(x + 1 + (width) * (z + 0)); // 오른쪽아래	 //

		}
	}



	

}

void Terrain::CreateNormal()
{
	for (UINT i = 0; i < indices.size() / 3; i++)
	{
		UINT index0		= indices[i * 3 + 0];
		UINT index1		= indices[i * 3 + 1];
		UINT index2		= indices[i * 3 + 2];
			
		Vector3 p0		= vertices[index0].pos;
		Vector3 p1		= vertices[index1].pos;
		Vector3 p2		= vertices[index2].pos;
		
		Vector3 v01		= p1 - p0;
		Vector3 v02		= p2 - p0;

		Vector3 normal	= Vector3::Cross(v01, v02).GetNormalize();
		

		vertices[index0].normal += normal;
		vertices[index1].normal += normal;
		vertices[index2].normal += normal;

	}



}
