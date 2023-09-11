#include "Framework.h"
#include "TerrainEditor.h"


TerrainEditor::TerrainEditor(UINT height, UINT width)
	: height(height), width(width)
{
	material = new Material();
	material->SetShader(L"NormalMapping");
	

	worldBuffer = new MatrixBuffer();


	CreateMesh();
	CreateNormal();
	CreateTangent();

	mesh = new Mesh(vertices, indices);
}

TerrainEditor::~TerrainEditor()
{
	delete worldBuffer;
	delete mesh;
	delete material;
}

void TerrainEditor::Update()
{
	Transform::Update();
}

void TerrainEditor::Render()
{
	worldBuffer->SetData(world);
	worldBuffer->SetVSBuffer(0);
	mesh->SetMesh();
	material->SetMaterial();

	DC->DrawIndexed(indices.size(), 0, 0);
}

void TerrainEditor::PostRender()
{
}

void TerrainEditor::Debug()
{
}

bool TerrainEditor::Picking(OUT Vector3* position)
{
	Ray ray = Camera::GetInstance()->ScreenPointToRay(MousePos);
	
	for (UINT z = 0; z < height - 1; z++)
	{
		for (UINT x = 0; x < width-1; x++)
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
				*position =  ray.origin + ray.direction * distance;

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

void TerrainEditor::CreateMesh()
{

	//  vertex
	for (float z = 0; z < height; z++)
	{
		for (float x = 0; x < width; x++)
		{
			VertexType vertex;

			vertex.pos = Vector3(x, 0, z);


			vertex.uv.x = x / (width - 1);
			vertex.uv.y = 1 - z / (height - 1);

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

void TerrainEditor::CreateNormal()
{
	for (UINT i = 0; i < indices.size() / 3; i++)
	{
		UINT index0 = indices[i * 3 + 0];
		UINT index1 = indices[i * 3 + 1];
		UINT index2 = indices[i * 3 + 2];

		Vector3 p0 = vertices[index0].pos;
		Vector3 p1 = vertices[index1].pos;
		Vector3 p2 = vertices[index2].pos;

		Vector3 v01 = p1 - p0;
		Vector3 v02 = p2 - p0;

		Vector3 normal = Vector3::Cross(v01, v02).GetNormalize();


		vertices[index0].normal += normal;
		vertices[index1].normal += normal;
		vertices[index2].normal += normal;

	}



}

void TerrainEditor::CreateTangent()
{
	for (UINT i = 0; i < indices.size() / 3; i++)
	{
		UINT index0 = indices[i * 3 + 0];
		UINT index1 = indices[i * 3 + 1];
		UINT index2 = indices[i * 3 + 2];

		Vector3 p0 = vertices[index0].pos;
		Vector3 p1 = vertices[index1].pos;
		Vector3 p2 = vertices[index2].pos;

		Vector2 uv0 = vertices[index0].uv;
		Vector2 uv1 = vertices[index1].uv;
		Vector2 uv2 = vertices[index2].uv;

		Vector3 e01 = p1 - p0;
		Vector3 e02 = p2 - p0;

		float u1 = uv1.x - uv0.x;
		float v1 = uv1.y - uv0.y;

		float u2 = uv2.x - uv0.x;
		float v2 = uv2.y - uv0.y;

		// Deteminent 판별식 
		float D = 1.0f / (u1 * v2 - v1 * u2);

		Vector3 tangent = D * (e01 * v2 - e02 * v1);

		vertices[index0].tangent += tangent;
		vertices[index1].tangent += tangent;
		vertices[index2].tangent += tangent;

	}

	for (VertexType& vertex : vertices)
	{
		Vector3 T = vertex.tangent;
		Vector3 N = vertex.normal;

		vertex.tangent = (T - N * Vector3::Dot(N, T)).GetNormalize();

	}



}
