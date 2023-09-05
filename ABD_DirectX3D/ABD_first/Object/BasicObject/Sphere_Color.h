#pragma once
class Sphere_Color : public Transform
{
public:

    Sphere_Color(float radius, Vector4 color);

    ~Sphere_Color();


    void Update();
    void PreRender();
    void Render();
   
  
   
    void CreateNormal();
    void CreateMesh(float radius, Vector4 color);
    
private:
    //vector<VertexColor> vertices;
    vector<VertexCube> vertices;
    vector<UINT>        indices;

    // Shader�� meterial�� �������
    Material* material;
    // Buffer�� mash�� �ٲܰ���
    Mesh* mesh;

    MatrixBuffer* worldBuffer;


};

