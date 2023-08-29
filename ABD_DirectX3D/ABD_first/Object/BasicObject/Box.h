#pragma once
class Box : public Transform
{
public:

	Box(Vector2 size = { 1, 1 });
	~Box();


	void Update();
	void Render();
	void PosRender();

	
private:
	Material* material;
	Mesh* mesh;

	vector<VertexTexture>		vertices;
	vector<UINT>				indices;

	

	MatrixBuffer* worldBuffer = nullptr;

};

