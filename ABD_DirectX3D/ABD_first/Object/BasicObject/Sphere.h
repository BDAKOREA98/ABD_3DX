#pragma once
class Sphere : public Transform
{
public:

    Sphere(float radius, Vector4 color);

    ~Sphere();


    void Update();
    void PreRender();
    void Render();
    void PostRender();
  
    void CreateSphereVertices(float radius = 1.0f, int sliceCount = 20, int stackCount = 20, Vector4 color = {0.0f,0.0f,0.0f,0.0f});
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

