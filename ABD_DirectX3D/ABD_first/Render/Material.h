#pragma once
class Material
{
public:
	Material();
	Material(wstring file);
	~Material();

	void SetVertexShader(wstring file);
	void SetPixelShader(wstring file);

	void SetShader(wstring file);
	void SetMaterial();

	void SetDiffuseMap(wstring file);
	void SetSpecularMap(wstring file);

	MaterialBuffer* GetBuffer() { return buffer; }

	void PostRender();

private:

	PixelShader* pixelShader = nullptr;
	VertexShader* vertexShader = nullptr;

	Texture* diffuseMap		= nullptr;
	Texture* specularMap	= nullptr;

	MaterialBuffer* buffer = nullptr;

};

