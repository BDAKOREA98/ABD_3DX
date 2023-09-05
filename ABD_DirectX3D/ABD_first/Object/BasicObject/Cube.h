#pragma once
class Cube : public Transform
{
    typedef VertexColorNormal VertexType;


public:




	Cube(Vector4 color);
	
	~Cube();


    void Update() ;
    void PreRender() ;
    void Render() ;
    
    void CreateMesh(Vector4 color);
   
    void CreateNormal();


private:

    vector<VertexType> vertices;
    vector<UINT>        indices;
        
    // Shader�� meterial�� �������
    Material* material;
    // Buffer�� mash�� �ٲܰ���
    Mesh*     mesh;
    
    MatrixBuffer*       worldBuffer;
      
    

};

