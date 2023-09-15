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

	bool Picking(OUT Vector3* position); // OUT : return���� ������ ���̴�. �Լ����� return���� ������ �������� ������ OUT�� ����Ѵ�.
	

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
	
	// CoumputeShader
	struct InputDesc
	{
		UINT index ;
		Vector3 v0, v1, v2;


	};

	struct OutputDesc
	{
		int isPicked;

		float u, v;

		float distance;

	};


	StructuredBuffer*	structuredBuffer;
	ComputeShader*		computeShader;
	RayBuffer*			rayBuffer;

	InputDesc*	input = nullptr;
	OutputDesc* output = nullptr;

	UINT		polygonCount;



};