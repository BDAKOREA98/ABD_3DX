#pragma once

class Quad : public Transform
{
public:

	
	Quad(Vector2 size = { 1, 1 });
	~Quad();


	void Update();
	void Render();

	


private:
	Material*					material;
	Mesh*						mesh;
	
	vector<VertexTextureNormal>		vertices;
	vector<UINT>				indices;

	

	MatrixBuffer*				worldBuffer = nullptr;

};

