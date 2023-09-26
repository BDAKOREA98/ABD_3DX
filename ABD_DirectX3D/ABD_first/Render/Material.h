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
	void SetNormalMap(wstring file);

	MaterialBuffer* GetBuffer() { return buffer; }

	void SelectMap();

	void PostRender();

	void Save(wstring file);
	void Load(wstring file);

	void SaveDialog();
	void LoadDialog();


private:

	PixelShader* pixelShader = nullptr;
	VertexShader* vertexShader = nullptr;

	Texture* diffuseMap		= nullptr;
	Texture* specularMap	= nullptr;
	Texture* normalMap		= nullptr;

	

	MaterialBuffer* buffer = nullptr;
	
	static int ID;
	string label = "";
	string projectDir;

};

