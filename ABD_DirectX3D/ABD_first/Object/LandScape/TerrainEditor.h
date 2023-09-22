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
	

	void SaveHeightMap(wstring file);
	void LoadHeightMap(wstring file);

	void SaveHeightDialog();
	void LoadHeightDialog();



private:
	void CreateMesh();
	void CreateNormal();
	void CreateTangent();
	void CreateCoumpute();

	void AdjustHeight();


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

	Vector3 pickerPos;

	BrushBuffer* brushBuffer;

	float adjustValue = 20.0f;

	bool isRaise = true;

};