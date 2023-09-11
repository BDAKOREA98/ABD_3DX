#pragma once




class TerrainEditor : public Transform
{
	typedef VertexTextureNormalTangent VertexType;
public:
	TerrainEditor(UINT height = 100, UINT width = 100);
	~TerrainEditor();

	void Update();
	void Render();
	void PostRender();

	void Debug();

	Material* GetMaterial() { return material; }

	bool Picking(OUT Vector3* position); // OUT : return값을 내보낼 것이다. 함수에서 return값을 여러개 내보내고 싶을때 OUT을 사용한다.
	

private:
	void CreateMesh();
	void CreateNormal();
	void CreateTangent();



private:
	vector<VertexType>	vertices;
	vector<UINT>				indices;

	Material* material;
	Mesh* mesh;

	MatrixBuffer* worldBuffer;

	UINT					width = 10;
	UINT					height = 10;

	Texture* heightMap;

	const float				MAP_HEIGHT = 20.0f;
	

};

