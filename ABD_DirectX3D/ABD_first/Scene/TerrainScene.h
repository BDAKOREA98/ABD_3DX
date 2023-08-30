#pragma once
class TerrainScene : public Scene
{
public:

	TerrainScene();
	~TerrainScene();


	// Scene��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void PreRender() override;
	virtual void Render() override;
	virtual void PostRender() override;



	void CreateMesh();
	
private:

	vector<VertexTexture>	vertices;
	vector<UINT>			indices;

	Material*				material;
	Mesh*					mesh;

	MatrixBuffer*			worldBuffer;

	UINT					width  = 10;
	UINT					height = 10;






};
