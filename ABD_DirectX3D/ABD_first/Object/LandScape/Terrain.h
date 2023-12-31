#pragma once
class Terrain : public Transform
{
public:
	Terrain(wstring diffuseFile, wstring heightFile);
	~Terrain();

	void Render();
	void Update();
	void PostRender();
	bool Picking(OUT Vector3* position); 
private:
	void CreateMesh();
	void CreateNormal();


private:
	vector<VertexTextureNormal>	vertices;
	vector<UINT>				indices;

	Material* material;
	Mesh* mesh;

	MatrixBuffer* worldBuffer;

	UINT					width = 10;
	UINT					height = 10;

	Texture* heightMap;

	const float				MAP_HEIGHT = 20.0f;




};

