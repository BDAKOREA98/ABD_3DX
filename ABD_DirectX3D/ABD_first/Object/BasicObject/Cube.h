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
    void PostRender();
    void CreateMesh(Vector4 color);
   
    void CreateNormal();


private:

    vector<VertexType> vertices;
    vector<UINT>        indices;
        
    // Shader는 meterial로 만들거임
    Material* material;
    // Buffer는 mash로 바꿀거임
    Mesh*     mesh;
    
    MatrixBuffer*       worldBuffer;
      
    

};

