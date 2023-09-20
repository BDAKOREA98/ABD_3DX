#include "Framework.h"
#include "Texture.h"

map<wstring, Texture*> Texture::textures = {};

Texture::Texture(ID3D11ShaderResourceView* srv, ScratchImage& image)
	: srv(srv), image(move(image))
{

}

Texture::~Texture()
{
	srv->Release();

}


Texture* Texture::Get(wstring file)
{

	file = L"Resource/_Texture/" + file;


	assert(PathFileExists(file.c_str()));




	if (textures.count(file) > 0)
	{
		return textures[file];
	}


	
	
	ScratchImage image;

	wstring extension = GetExtension(file);
	if (extension == L"tga")
	{
		LoadFromTGAFile(file.c_str(), nullptr, image);
	}
	else if (extension == L"dds")
	{
		LoadFromDDSFile(file.c_str(), DDS_FLAGS_NONE, nullptr, image);
	}
	else
	{
		LoadFromWICFile(file.c_str(), WIC_FLAGS_NONE, nullptr, image);
	}







	

	ID3D11ShaderResourceView* srv = nullptr;

	CreateShaderResourceView
	(
		DEVICE,
		image.GetImages(),
		image.GetImageCount(),
		image.GetMetadata(),
		&srv
	);


	textures[file] = new Texture(srv, image);

	return textures[file];
}

void Texture::Delete()
{
	for (pair<wstring, Texture*> pair : textures)
	{
		delete pair.second;
	}
	textures.clear();
}

void Texture::PSSetShaderResource(UINT slot)
{
	DC->PSSetShaderResources(slot, 1, &srv);
}

vector<Vector4> Texture::ReadPixel()
{
	// 색깔 RGBA로 쓰기 위해 Vector4임
	// 이미지의 존재하는 모든 pixel의 색상을 받아서 사용할 것임
	// uint_t == unsigned charactor임
	// 
	

	unsigned char* pixels = image.GetPixels();
	
	// 픽셀의 총 갯수 ex) 1280*720
	UINT size = image.GetPixelsSize() * 0.25;
	
	vector<Vector4> colors(size);

	float scale = 1.0f / 255.0f;

	UINT count = 0;

	for (Vector4& color : colors)
	{
		color.x = pixels[count++] * scale;
		color.y = pixels[count++] * scale;
		color.z = pixels[count++] * scale;
		color.w = pixels[count++] * scale;
	
	}




	
	return colors;

}
