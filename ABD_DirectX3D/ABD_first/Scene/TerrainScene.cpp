#include "Framework.h"
#include "TerrainScene.h"

TerrainScene::TerrainScene()
{
	material = new Material();
	material->SetShader(L"Texture");
	material->SetDiffuseMap(L"LandScape/dirt.png");


	worldBuffer = new MatrixBuffer();


	heightMap = Texture::Get(L"HeightMap/HeightMap.png");

	CreateMesh();
}

TerrainScene::~TerrainScene()
{
	delete worldBuffer;
	delete mesh;
	delete material;

}

void TerrainScene::Update()
{
}

void TerrainScene::PreRender()
{
}

void TerrainScene::Render()
{
	worldBuffer	->	SetVSBuffer(0);
	mesh		->	SetMesh();
	material	->	SetMaterial();

	DC->DrawIndexed(indices.size(), 0, 0);
}

void TerrainScene::PostRender()
{

}

void TerrainScene::CreateMesh()
{
	
	
	width  = heightMap->GetSize().x;
	height = heightMap->GetSize().y;
	
	vector<Vector4> colors = heightMap->ReadPixel();



	//  vertex
	for (float z = 0; z < height; z++)
	{
		for (float x = 0; x < width; x++)
		{
			VertexTexture vertex;
			vertex.pos = Vector3(x, 0, z);
			

			vertex.uv.x =		x / (width	-1);
			vertex.uv.y = 1 -	z / (height	-1);

			/////////////HeightMap
			UINT index = x + z * width;
			 
			vertex.pos.y = colors[index].x * MAP_HEIGHT;



			
			vertices.push_back(vertex);

		}
	}
	
	//indices
	for (float z = 0; z < height-1; z++)
	{
		for (float x = 0; x < width -1; x++)
		{
			
			indices.push_back(x + 0 + (width) * (z + 1)); // 왼쪽위		//
			indices.push_back(x + 1 + (width) * (z + 1)); // 오른쪽위	//
			indices.push_back(x + 0 + (width) * (z + 0)); // 왼쪽아래    //


			indices.push_back(x + 0 + (width) * (z + 0)); // 왼쪽아래     //
			indices.push_back(x + 1 + (width) * (z + 1)); // 오른쪽위	//
			indices.push_back(x + 1 + (width) * (z + 0)); // 오른쪽아래	 //
			
		}
	}


	
	mesh = new Mesh(vertices, indices);

}
