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

	if (textures.count(file) > 0)
	{
		return textures[file];
	}

	
	
	ScratchImage image;


	LoadFromWICFile(file.c_str(), WIC_FLAGS_NONE, nullptr, image);

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
