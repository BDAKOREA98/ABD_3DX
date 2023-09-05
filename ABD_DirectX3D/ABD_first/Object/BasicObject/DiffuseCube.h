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
    
    void CreateMesh(Vector4 color);
    void CreateNormal();

private:

    vector<VertexCube> vertices;
    vector<UINT>        indices;

    // Shader�� meterial�� �������
    Material* material;
    // Buffer�� mash�� �ٲܰ���
    Mesh* mesh;

    MatrixBuffer* worldBuffer;



};

