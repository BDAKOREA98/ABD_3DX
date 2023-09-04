#pragma once
class DiffuseCube : public Transform
{

    typedef VertexCube VertexType;

public:

    DiffuseCube(Vector4 color);

    ~DiffuseCube();


    void Update();
    void PreRender();
    void Render();
    void PostRender();
    void CreateMesh(Vector4 color);
    void CreateNormal();

private:

    vector<VertexCube> vertices;
    vector<UINT>        indices;

    // Shader는 meterial로 만들거임
    Material* material;
    // Buffer는 mash로 바꿀거임
    Mesh* mesh;

    MatrixBuffer* worldBuffer;



};

