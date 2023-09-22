#include "Framework.h"
#include "TerrainEditor.h"


TerrainEditor::TerrainEditor(UINT height, UINT width)
	: height(height), width(width)
{
	material = new Material();
	material->SetShader(L"TerrainBrush");

	worldBuffer = new MatrixBuffer();

	//heightMap = Texture::Load(L"HeightMap/ColorMap256.png");

	BinaryReader data(L"ASDASDASD");

	if (data.Succeeded())
	{
		wstring heightPath = data.ReadWstring();

		heightMap = Texture::Load(heightPath);
	}
	CreateMesh();
	CreateNormal();
	CreateTangent();

	mesh = new Mesh(vertices, indices);

	rayBuffer = new RayBuffer();
	computeShader = Shader::GetCS(L"ComputePicking");

	
	CreateCoumpute();

	brushBuffer = new BrushBuffer;
	
	
	


}

TerrainEditor::~TerrainEditor()
{

	if (heightMap != nullptr)
	{
		BinaryWriter data(L"ASDASDASD");

		data.WriteData(heightMap->GetPath());
	}


	delete worldBuffer;
	delete mesh;
	delete material;
	
	delete[] input;
	delete[] output;


	delete rayBuffer;
	delete structuredBuffer;

	delete brushBuffer;
}

void TerrainEditor::Update()
{
	Transform::Update();

	brushBuffer->data.location = pickerPos;

	if (Picking(&pickerPos)&&KEY_PRESS(VK_LBUTTON) && !ImGui::GetIO().WantCaptureMouse)
	{
		AdjustHeight();
	}

	if (KEY_PRESS(VK_LSHIFT))
	{
		isRaise = false;
	}
	else
	{
		isRaise = true;
	}
}

void TerrainEditor::Render()
{
	worldBuffer->SetData(world);
	worldBuffer->SetVSBuffer(0);
	mesh->SetMesh();
	material->SetMaterial();

	brushBuffer->SetPSBuffer(10);

	DC->DrawIndexed(indices.size(), 0, 0);
}

void TerrainEditor::PostRender()
{
	
}

void TerrainEditor::Debug()
{
	ImGui::Text("PickerPos : %0.4f, %0.4f, %0.4f", pickerPos.x, pickerPos.y, pickerPos.z);

	ImGui::ColorEdit3("BrushColor : ", (float*)&brushBuffer->data.color);

	ImGui::SliderFloat("BrushIntensity ", &adjustValue, 1.0f, 50.0f);

	ImGui::SliderFloat("Range ", &brushBuffer->data.range, 1.0f, 50.0f);
	
	ImGui::SliderInt("type ", &brushBuffer->data.type, 1.0f, 3.0f);

	const char* typeList[] = { "circle","hole", "halfRangeRect", "rangeRect"};

	ImGui::Combo("BrushType", & brushBuffer->data.type, typeList, 4);
	

	
	SaveHeightDialog();
	LoadHeightDialog();
	


}

bool TerrainEditor::Picking(OUT Vector3* position)
{


	Ray ray = Camera::GetInstance()->ScreenPointToRay(MousePos);
	
	rayBuffer->data.origin		= ray.origin;
	rayBuffer->data.direction	= ray.direction;
	rayBuffer->data.outputSize	= polygonCount;

	rayBuffer->SetCSBuffer(0);
	////////////////////////////////////////////

	structuredBuffer->SetSRV();
	structuredBuffer->SetUAV();
	
	computeShader->SetShader();

	UINT groupCount = ceil(polygonCount / 1024.0f); 

	DC->Dispatch(groupCount, 1, 1);
	
	structuredBuffer->Copy(output, sizeof(OutputDesc) * polygonCount);
	


	float minDistance = FLT_MAX;
	
	
	

	for (UINT i = 0; i < polygonCount; i++)
	{
		if (output[i].isPicked)
		{
			if (minDistance > output[i].distance)
			{
				minDistance = output[i].distance;
				
			}	
		}
	}
	if (minDistance < FLT_MAX)
	{
		*position = ray.origin + ray.direction * minDistance;
		
		

		return true;
	}



	return false;
}

void TerrainEditor::SaveHeightMap(wstring file)
{
	file = L"Resource/_Texture/" + file;

	UINT size = width * height * 4;
	
	// UINT_t = unsigned char
	uint8_t* pixels = new uint8_t[size];

	for (UINT i = 0; i < size / 4; i++)
	{
		float y = vertices[i].pos.y;

		uint8_t height = y * 255 / MAP_HEIGHT;

		pixels[4 * i + 0] = height;
		pixels[4 * i + 1] = height;
		pixels[4 * i + 2] = height;
		pixels[4 * i + 3] = 255;

	}

	Image image;
	image.width			= width;
	image.height		= height;
	image.pixels		= pixels;
	image.format		= DXGI_FORMAT_R8G8B8A8_UNORM;
	image.rowPitch		= width * 4;
	image.slicePitch	= size;
	
	


	SaveToWICFile(image, WIC_FLAGS_FORCE_RGB, GetWICCodec(WIC_CODEC_PNG), file.c_str());




}

void TerrainEditor::LoadHeightMap(wstring file)
{

	//file = L"HeightMap/" + file;

	heightMap = Texture::Load(file);

	if (mesh != nullptr)
	{
		delete mesh;
	}
	vertices.clear();
	indices.clear();

	CreateMesh();
	CreateNormal();
	CreateTangent();

	mesh = new Mesh(vertices, indices);
	
	

}

void TerrainEditor::SaveHeightDialog()
{
	if (ImGui::Button("Save HeightMap"))
	{
		Dialog->OpenDialog("SaveKey", "Save", ".png", "Resource/_Texture/HeightMap/");
	}

	

	if (Dialog->Display("SaveKey", 32, { 200,100 }))
	{
		if (Dialog->IsOk())
		{
			string path = Dialog->GetFilePathName();

			path = path.substr(GetTextureDir().size(), path.length());
			
			SaveHeightMap(ToWstring(path));


		}

		Dialog->Close();
	}
}

void TerrainEditor::LoadHeightDialog()
{
	if (ImGui::Button("Load HeightMap"))
	{
		Dialog->OpenDialog("LoadKey", "Load", ".png", "Resource/_Texture/HeightMap/");
	}



	if (Dialog->Display("LoadKey", 32, { 200,100 }))
	{
		if (Dialog->IsOk())
		{
			string path = Dialog->GetFilePathName();

			path = path.substr(GetTextureDir().size(), path.length());

			LoadHeightMap(ToWstring(path));


		}

		Dialog->Close();
	}
}

void TerrainEditor::CreateCoumpute()
{
	polygonCount = indices.size() / 3;

	if (input != nullptr)
	{
		delete input;
	}


	input = new InputDesc[polygonCount];

	for (UINT i = 0; i < polygonCount; i++)
	{
		input[i].index = i;

		UINT index0 = indices[i * 3 + 0];
		UINT index1 = indices[i * 3 + 1];
		UINT index2 = indices[i * 3 + 2];


		input[i].v0 = vertices[index0].pos;
		input[i].v1 = vertices[index1].pos;
		input[i].v2 = vertices[index2].pos;

	}

	if (structuredBuffer != nullptr)
	{
		delete structuredBuffer;
	}

	structuredBuffer = new StructuredBuffer
	(
		input,
		sizeof(InputDesc),
		polygonCount,
		sizeof(OutputDesc),
		polygonCount
	);

	if (output != nullptr)
	{
		delete output;
	}

	output = new OutputDesc[polygonCount];
	
}

void TerrainEditor::CreateMesh()
{

	vector<Vector4> colors;
	if (heightMap != nullptr)
	{
		width = heightMap->GetSize().x;
		height = heightMap->GetSize().y;
		colors = heightMap->ReadPixel();
	}
	


	//  vertex
	for (float z = 0; z < height; z++)
	{
		for (float x = 0; x < width; x++)
		{
			VertexType vertex;

			vertex.pos = Vector3(x, 0, z);


			vertex.uv.x = x / (width - 1);
			vertex.uv.y = 1 - z / (height - 1);

			if (colors.size() > 0)
			{
				/////////////HeightMap
				UINT index = x + z * width;
				vertex.pos.y = colors[index].x * MAP_HEIGHT;
			}

			
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
	for (VertexType& vertex : vertices)
	{
		vertex.normal = Vector3();
	}

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

	for (VertexType& vertex : vertices)
	{
		vertex.tangent = Vector3();
	}

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

void TerrainEditor::AdjustHeight()
{
	switch (brushBuffer->data.type)
	{
	case 0:
		for (VertexType& vertex : vertices)
		{
			Vector3 p1 = Vector3(vertex.pos.x, 0.0f, vertex.pos.z);
			Vector3 p2 = Vector3(pickerPos.x, 0.0f, pickerPos.z);

			float distance = (p1 - p2).Length();
			
			float value = adjustValue * max(0, cos(XM_PIDIV2* distance / brushBuffer->data.range));



			if (distance <= brushBuffer->data.range)
			{
				if (isRaise)
				{
					vertex.pos.y += value * Time::Delta();
				}
				else
				{
					vertex.pos.y -= value * Time::Delta();
				}
				if (vertex.pos.y > MAP_HEIGHT)
				{
					vertex.pos.y = MAP_HEIGHT;
				}
				if (vertex.pos.y < 0)
				{
					vertex.pos.y = 0;
				}

			}
		}
		break;
	case 1:
		for (VertexType& vertex : vertices)
		{
			Vector3 p1 = Vector3(vertex.pos.x, 0.0f, vertex.pos.z);
			Vector3 p2 = Vector3(pickerPos.x, 0.0f, pickerPos.z);

			float distance = (p1 - p2).Length();

			float value = adjustValue ;



			if (distance >= brushBuffer->data.range && distance <= (brushBuffer->data.range * 2))
			{
				if (isRaise)
				{
					vertex.pos.y += value * Time::Delta();
				}
				else
				{
					vertex.pos.y -= value * Time::Delta();
				}
				if (vertex.pos.y > MAP_HEIGHT)
				{
					vertex.pos.y = MAP_HEIGHT;
				}
				if (vertex.pos.y < 0)
				{
					vertex.pos.y = 0;
				}
			}
		}
		break;
	case 2:
		for (VertexType& vertex : vertices)
		{
			Vector3 p1 = Vector3(vertex.pos.x, 0.0f, vertex.pos.z);
			Vector3 p2 = Vector3(pickerPos.x, 0.0f, pickerPos.z);


			float deltaX = abs(p1.x - p2.x);
			float deltaZ = abs(p1.z - p2.z);

			float halfWidth = brushBuffer->data.range / 2.0f;
			float halfHeight = brushBuffer->data.range / 2.0f;

			
			
			if (deltaX <= halfWidth && deltaZ <= halfHeight)
			{
				if (isRaise)
				{
					vertex.pos.y += adjustValue * Time::Delta();
				}
				else
				{
					vertex.pos.y -= adjustValue * Time::Delta();
				}
				if (vertex.pos.y > MAP_HEIGHT)
				{
					vertex.pos.y = MAP_HEIGHT;
				}
				if (vertex.pos.y < 0)
				{
					vertex.pos.y = 0;
				}
			}
		}
		break;

	case 3:
		for (VertexType& vertex : vertices)
		{
			Vector3 p1 = Vector3(vertex.pos.x, 0.0f, vertex.pos.z);
			Vector3 p2 = Vector3(pickerPos.x, 0.0f, pickerPos.z);

			Vector3 distance = p1 - p2;



			if (abs(distance.x) <= brushBuffer->data.range && 
				abs(distance.z) <= brushBuffer->data.range)
			{
				if (isRaise)
				{
					vertex.pos.y += adjustValue * Time::Delta();
				}
				else
				{
					vertex.pos.y -= adjustValue * Time::Delta();
				}
				if (vertex.pos.y > MAP_HEIGHT)
				{
					vertex.pos.y = MAP_HEIGHT;
				}
				if (vertex.pos.y < 0)
				{				   
					vertex.pos.y = 0;
				}
			}
		}
		break;

	default:
		break;
	}

	
	
	CreateNormal();
	CreateTangent();

	mesh->UpdateVertex(vertices.data(), vertices.size());

	for (UINT i = 0; i < polygonCount; i++)
	{
		input[i].index = i;

		UINT index0 = indices[i * 3 + 0];
		UINT index1 = indices[i * 3 + 1];
		UINT index2 = indices[i * 3 + 2];


		input[i].v0 = vertices[index0].pos;
		input[i].v1 = vertices[index1].pos;
		input[i].v2 = vertices[index2].pos;

	}
	
	structuredBuffer->UpdateInput(input);



}
