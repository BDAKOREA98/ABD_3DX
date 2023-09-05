#pragma once
class Sphere_Texture : public Transform
{
	typedef VertexTextureNormal VertexType;

public:

	Sphere_Texture(float radius = 1.0f, UINT sliceCount = 20, UINT stackCount = 10);
	~Sphere_Texture();

		void Render();
		void Update();
		

private:

	void CreateMesh();
	
	



private:

	Material* material;
	Mesh* mesh;

	vector<VertexType>		vertices;
	vector<UINT>				indices;

	UINT sliceCount;
	UINT stackCount;
	float radius;


	MatrixBuffer* worldBuffer = nullptr;

};

