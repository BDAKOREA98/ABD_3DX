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
	
	
	worldBuffer = new MatrixBuffer();


	///////////////////////////////////////////////////////// Texture
	
	ScratchImage image;
	LoadFromWICFile(L"Resource/_Texture/Landscape/box.png", WIC_FLAGS_NONE, nullptr, image);

	CreateShaderResourceView
	(
		DEVICE,
		image.GetImages(),
		image.GetImageCount(),
		image.GetMetadata(),
		&srv
	);

	D3D11_SAMPLER_DESC samplerDesc = {};

	samplerDesc.Filter			 =		D3D11_FILTER_MIN_MAG_MIP_POINT;
	samplerDesc.AddressU		 =		D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV		 =		D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW		 =		D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.ComparisonFunc   =		D3D11_COMPARISON_NEVER;
	samplerDesc.MinLOD			 =		0;
	samplerDesc.MaxLOD			 =		D3D11_FLOAT32_MAX;


	DEVICE->CreateSamplerState(&samplerDesc, &samplerState);



}

Quad::~Quad()
{
	delete mesh;
	delete worldBuffer;

	srv->Release();
	samplerState->Release();

	
	

}

void Quad::Update()
{
	if (Key_PRESS(VK_LEFT))
	{
		
	}
}

void Quad::Render()
{

	//  부모에 있는 월드
	worldBuffer->SetData(world);
	worldBuffer->SetVSBuffer(0);
	

	material->SetMaterial();
	mesh	->SetMesh();


	DC->PSSetShaderResources(0, 1, &srv);
	DC->PSSetSamplers(0, 1, &samplerState);





	// draw하기전에만 설정하자
	DC->DrawIndexed(indices.size(), 0, 0);


}
