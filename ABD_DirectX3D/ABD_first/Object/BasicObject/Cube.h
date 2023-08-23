#pragma once
class Cube : public Transform
{
public:

	Cube(Vector4 color);
	
	~Cube();


    void Update() ;

    void PreRender() ;

    void Render() ;

    void PostRender();

    void CreateMesh(Vector4 color);

    void Debug();

private:


    vector<VertexColor> vertices;
    vector<UINT>        indices;

    
    // Shader�� meterial�� �������
    Material* material;
    // Buffer�� mash�� �ٲܰ���
    Mesh*     mesh;


  

    MatrixBuffer*       worldBuffer;

    
  
    static int count;
    string label = "";

};

