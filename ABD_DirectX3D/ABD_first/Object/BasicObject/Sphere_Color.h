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

    // Shader는 meterial로 만들거임
    Material* material;
    // Buffer는 mash로 바꿀거임
    Mesh* mesh;

    MatrixBuffer* worldBuffer;


};

